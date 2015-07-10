#include "Server.h"


Server::Server()
{
	init();
}

NetworkClient& Server::initClient(SOCKET csock)
{
	NetworkClient c;
	c.sock = csock;
	c.name = std::string("Visiteur_") + std::to_string(nb_clients_all_time);
	c.id = nb_clients_all_time;
	c.x = rand() % 500;
	c.y = rand() % 500;
	c.angle = rand() % 360;
	clients.push_back(c);
	return c;
}

void Server::newClientConnection(NetworkClient* client)
{
	sendOneClientCoordToAllClients(client);
}

void Server::sendAllClientsCoordToAllClients()
{
	for each (NetworkClient c in clients)
	{
		sendOneClientCoordToAllClients(&c);
	}
}

void Server::sendOneClientCoordToAllClients(NetworkClient* client)
{
	sendMessageToAllClients(createCoordMessage(client));
}

void Server::sendAllClientsCoordToOneClient(NetworkClient* listener)
{
	for each (NetworkClient c in clients)
	{
		sendOneClientCoordToOneClient(&c, listener);
	}
}

void Server::sendOneClientCoordToOneClient(NetworkClient* client, NetworkClient* listener)
{
	sendMessageToOneClient(listener, createCoordMessage(client));
}

std::string Server::createCoordMessage(NetworkClient* client)
{
	return std::string("P") + std::to_string(client->id) +
		std::string("-") + std::to_string(client->x) +
		std::string("-") + std::to_string(client->y) +
		std::string("-") + std::to_string(client->angle);
}

void Server::sendMessageToAllClients(std::string message)
{
	for each (NetworkClient c in clients)
	{
		sendMessageToOneClient(&c, message);
	}
}

void Server::sendMessageToOneClient(NetworkClient* listener, std::string message)
{
	send(listener->sock, (message).c_str(), message.length(), 0);
}

DWORD WINAPI Server::createThreadListenOnServer(LPVOID  client)
{
	CoupleServerClient* c = (CoupleServerClient*)client;
	return c->server->listenForMessage(c->client);
}

void Server::removeClient(NetworkClient* c)
{
	sendMessageToAllClients(std::string("X") + std::to_string(c->id));
	nb_clients--;
	closesocket(c->sock);
	clients.remove(*c);
}

int Server::listenForMessage(NetworkClient* c)
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
			case 'Z':
				sendMessageToAllClients(std::string("Z") + std::to_string(c->id));
				break;
			case 'Q':
				sendMessageToAllClients(std::string("Q") + std::to_string(c->id));
				break;
			case 'S':
				sendMessageToAllClients(std::string("S") + std::to_string(c->id));
				break;
			case 'D':
				sendMessageToAllClients(std::string("D") + std::to_string(c->id));
				break;
			case 'X':
				removeClient(c);
				end = true;
				break;
			}
		}
	}
	return 0;
}

void Server::listenForClientsConnections(SOCKADDR_IN sin, SOCKET sock)
{
	HANDLE  hThreadArray[10];
	DWORD   dwThreadIdArray[10];
	while (true)
	{
		int sizeof_sin = sizeof(sin);
		SOCKET csock = accept(sock, (SOCKADDR *)&sin, &sizeof_sin);
		if (csock != INVALID_SOCKET)
		{
			NetworkClient& c = initClient(csock);
			CoupleServerClient couple;
			couple.client = &c;
			couple.server = this;
			hThreadArray[nb_clients] = CreateThread(
				NULL,                   // default security attributes
				0,                      // use default stack size  
				createThreadListenOnServer,       // thread function name
				&c,          // argument to thread function 
				0,                      // use default creation flags 
				&dwThreadIdArray[nb_clients]);
			nb_clients_all_time++;
		}
	}
}

void Server::init()
{
	int nb_clients = 0;
	bool end = false;
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
	listenForClientsConnections(sin, sock);
}


Server::~Server()
{
	closesocket(sock);
	WSACleanup();
}


int main()
{

}