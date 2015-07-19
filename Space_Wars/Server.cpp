#include "Server.h"


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

Server::Server()
{
	init();
}

std::shared_ptr<NetworkClient> Server::initClient(SOCKET csock)
{
	std::shared_ptr<NetworkClient> c = std::shared_ptr<NetworkClient>(new NetworkClient());
	c->sock = csock;
	c->name = std::string("Visiteur_") + std::to_string(nb_clients_all_time);
	c->id = nb_clients_all_time;
	c->pos = glm::vec3(rand() % 500, rand() % 500, rand() % 500);
	c->orientation = glm::vec3(rand() % 500, rand() % 500, rand() % 500);
	c->ping = true;
	c->pingAttemps = 0;
	clients.push_back(c);
	return c;
}

void Server::newClientConnection(std::shared_ptr<NetworkClient> client)
{
	sendOneClientCoordToAllClients(client, true);
	sendMessageToOneClient(client, std::string("Y-") + std::to_string(client->id));
}

void Server::sendAllClientsCoordToAllClients(bool n)
{
	for each (auto c in clients)
	{
		sendOneClientCoordToAllClients(c, n);
	}
}

void Server::sendOneClientCoordToAllClients(std::shared_ptr<NetworkClient> client, bool n)
{
	sendMessageToAllClients(createCoordMessage(client, n));
}

void Server::sendAllClientsCoordToOneClient(std::shared_ptr<NetworkClient> listener, bool n)
{
	for each (auto c in clients)
	{
		sendOneClientCoordToOneClient(c, listener, n);
	}
}

void Server::sendOneClientCoordToOneClient(std::shared_ptr<NetworkClient> client, std::shared_ptr<NetworkClient> listener, bool n)
{
	sendMessageToOneClient(listener, createCoordMessage(client, n));
}

std::string Server::createCoordMessage(std::shared_ptr<NetworkClient> client, bool n)
{
	std::string s1;
	if (n)
		s1 = std::string("N-");
	else
		s1 = std::string("P-");
	return s1 + std::to_string(client->id) +
		std::string("-") + std::to_string(client->pos.x) +
		std::string("-") + std::to_string(client->pos.y) +
		std::string("-") + std::to_string(client->pos.z) +
		std::string("-") + std::to_string(client->orientation.x) +
		std::string("-") + std::to_string(client->orientation.y) +
		std::string("-") + std::to_string(client->orientation.z);
}

void Server::sendMessageToAllClients(std::string message)
{
	for each (auto c in clients)
	{
		sendMessageToOneClient(c, message);
	}
}

void Server::sendMessageToOneClient(std::shared_ptr<NetworkClient> listener, std::string message)
{
	send(listener->sock, (message).c_str(), message.length(), 0);
}

DWORD WINAPI Server::createThreadListenOnServer(LPVOID  client)
{
	CoupleServerClient* c = (CoupleServerClient*)client;
	return c->server->listenForMessage(c->client);
}

DWORD WINAPI Server::createThreadPingAllClients(LPVOID server)
{
	Server* s = (Server*)server;
	return s->pingAllClients();
}

int Server::pingAllClients()
{
	std::vector<std::shared_ptr<NetworkClient>> clientsToRemove = std::vector<std::shared_ptr<NetworkClient>>();
	int i = 0;
	while (true)
	{
		for each (auto c in clients)
		{
			if (!c->ping)
			{
				c->pingAttemps++;
				if (c->pingAttemps > 2)
				{
					removeClientDependencies(c);
					clientsToRemove.push_back(c);
				}
			}
			c->ping = false;
			sendMessageToAllClients(std::string("H"));
		}
		for each (auto cToRemove in clientsToRemove)
		{
			removeClientFromList(cToRemove);
		}
		clientsToRemove.empty();
		Sleep(1000);
		i++;
		if (i == 3)
		{
			i = 0;
			sendAllClientsCoordToAllClients(false);
		}
	}
	return 0;
}

void Server::recivePingFromClient(std::shared_ptr<NetworkClient> c)
{
	c->ping = true;
}

void Server::removeClientDependencies(std::shared_ptr<NetworkClient> c)
{
	sendMessageToAllClients(std::string("X-") + std::to_string(c->id));
	nb_clients--;
	closesocket(c->sock);
	CloseHandle(c->threadHandle); // Termine le thread listen message for this player
}

void Server::removeClientFromList(std::shared_ptr<NetworkClient> c)
{
	clients.remove_if([c](std::shared_ptr<NetworkClient> c2){ return c2->id == c->id; });
}

void Server::updateRotation(std::shared_ptr<NetworkClient> c, std::string str)
{
	std::vector<std::string> elems = split(str, '-');
	c->orientation.x = std::stof(elems.at(1));
	c->orientation.y = std::stof(elems.at(2));
	c->orientation.z = std::stof(elems.at(3));
	glm::normalize(c->orientation);
}

int Server::listenForMessage(std::shared_ptr<NetworkClient> c)
{
	newClientConnection(c);
	int size = 0;
	bool end = false;
	while (!end)
	{
		size = recv(c->sock, chars, 15, 0);
		if (size > 0)
		{
			switch (chars[0])
			{
			case 'R':
				updateRotation(c, std::string(chars));
				sendOneClientCoordToAllClients(c, false);
				break;
			case 'T':
				createProjectile(c);
				break;
			case 'H':
				recivePingFromClient(c);
				break;
			case 'X':
				removeClientDependencies(c);
				removeClientFromList(c);
				end = true;
				break;
			}
		}
	}
	return 0;
}


void Server::createProjectile(std::shared_ptr<NetworkClient> c)
{
	Projectile p = Projectile();
	p.position = c->pos;
	p.orientation = c->orientation * 2.0f;
	sendMessageToAllClients(std::string("T-") + std::to_string(p.position.x) +
		std::string("-") + std::to_string(p.position.y) +
		std::string("-") + std::to_string(p.position.z) +
		std::string("-") + std::to_string(p.orientation.x) +
		std::string("-") + std::to_string(p.orientation.y) +
		std::string("-") + std::to_string(p.orientation.z)
	);
	p.owner = c;
	projectiles.push_back(std::shared_ptr<Projectile>(&p));
}

void Server::listenForClientsConnections(SOCKADDR_IN sin, SOCKET sock)
{
	while (true)
	{
		int sizeof_sin = sizeof(sin);
		SOCKET csock = accept(sock, (SOCKADDR *)&sin, &sizeof_sin);
		if (csock != INVALID_SOCKET)
		{
			std::shared_ptr<NetworkClient> c = initClient(csock);
			CoupleServerClient couple;
			couple.client = c;
			couple.server = this;
			c->threadHandle = CreateThread(
				NULL,                   // default security attributes
				0,                      // use default stack size  
				createThreadListenOnServer,       // thread function name
				&couple,          // couple with server and client 
				0,                      // use default creation flags 
				&(c->threadId) // return thread ID
			);
			nb_clients_all_time++;
		}
		else
		{
			std::cout << WSAGetLastError() << std::endl;
		}
	}
}

void Server::init()
{
	nb_clients_all_time = 0;
	clients = std::list<std::shared_ptr<NetworkClient>>();
	nb_clients = 0;
	std::string str = "";
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(34567);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(sock, (SOCKADDR *)&sin, sizeof(sin));
	listen(sock, 0);
	pingThreadHandle = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		createThreadPingAllClients,       // thread function name
		this,          // couple with server and client 
		0,                      // use default creation flags 
		&(pingThreadId) // return thread ID
		);
	gameLoopThreadHandle = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		createGameLoop,       // thread function name
		this,          // couple with server and client 
		0,                      // use default creation flags 
		&(gameLoopThreadId) // return thread ID
		);
	listenForClientsConnections(sin, sock);
}

DWORD WINAPI Server::createGameLoop(LPVOID server)
{
	Server* s = (Server*)server;
	s->gameLoop();
	return 0;
}

void Server::gameLoop()
{
	clock_t t;
	int begin = 0;
	while (true)
	{
		t = clock();
		for each (auto c in clients)
		{
			c->pos += c->orientation;
		}
		for each (auto p in projectiles)
		{
			p->position += p->orientation;
			for each (auto c in clients)
			{
				if (p->owner->id != c->id && std::abs(glm::distance(c->pos, p->position)) < 10.0f)
				{
					sendMessageToAllClients(std::string("S-") + std::to_string(p->owner->id) +
						std::string("-") + std::to_string(c->id));
				}
			}
		}
		Sleep(166 - (clock() - t));
	}
}

Server::~Server()
{
	closesocket(sock);
	WSACleanup();
}


