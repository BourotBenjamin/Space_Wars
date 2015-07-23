#include "Client.h"


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



void Client::createPlayer(std::string& str)
{
	cv_m.lock();
	std::vector<std::string> elems = split(str, ';');
	std::shared_ptr<PlayerGL> p = std::shared_ptr<PlayerGL>(new PlayerGL());
	p->setId(std::stoi(elems.at(1)));
	float f = std::stof(elems.at(2));
	p->setPos(std::stof(elems.at(2)), std::stof(elems.at(3)), std::stof(elems.at(4)));
	p->doRoation(std::stof(elems.at(5)), std::stof(elems.at(6)));
	players.push_back(p);
	cv_m.unlock();
}

std::shared_ptr<PlayerGL> Client::getPlayerAt(int index)
{
	for each(std::shared_ptr<PlayerGL> p in players)
	{
		if (p->getId() == index)
			return p;
	}
	return nullptr;
}

void Client::updatePlayer(std::string& str)
{
	cv_m.lock();
	std::vector<std::string> elems = split(str, ';');
	std::shared_ptr<PlayerGL> p = getPlayerAt(std::stoi(elems.at(1)));
	if (p)
	{
		p->setId(std::stoi(elems.at(1)));
		p->setPos(std::stof(elems.at(2)), std::stof(elems.at(3)), std::stof(elems.at(4)));
		p->doRoation(std::stof(elems.at(5)), std::stof(elems.at(6)));
	}
	cv_m.unlock();
}

void Client::removePlayer(std::string& str)
{
	cv_m.lock();
	std::vector<std::string> elems = split(str, ';');
	int i = std::stoi(elems.at(1));
	players.remove_if([i](std::shared_ptr<PlayerGL> p){ return p->getId() == i; });
	cv_m.unlock();
}

Client::Client()
{
	init();
}


Client::~Client()
{
	for each(std::shared_ptr<PlayerGL> p in players)
	{
		p.reset();
	}
	sendMessage("X");
	closesocket(sock);
	WSACleanup();
}


DWORD WINAPI Client::createThreadListenOnClient(LPVOID c)
{
	Client* client = (Client*)c;
	return client->listenForMessage();
}

int Client::listenForMessage()
{
	int size = 0;
	while (true)
	{
		size = recv(sock, chars, 90, 0);
		if (size > 0)
		{
			std::string s(chars, chars + size);
			char c0 = s.at(0);
			switch (c0)
			{
			case 'C':
				collision(s);
				break;
			case 'N':
				createPlayer(s);
				break;
			case 'P':
				updatePlayer(s);
				break;
			case 'X':
				removePlayer(s);
				break;
			case 'H':
				sendMessage(std::string("H"));
				break;
			case 'S':
				removeProjectile(s);
				break;
			case 'T':
				createProjectile(s);
				break;
			case 'Y':
				std::vector<std::string> elems = split(s, ';');
				selfId = std::stoi(elems.at(1));
				break;
			}
			std::cout << s << std::endl;
		}
	}
	return 0;
}

void Client::collision(std::string& str)
{
	cv_m.lock();
	std::vector<std::string> elems = split(str, ';');
	std::shared_ptr<PlayerGL> p = getPlayerAt(std::stoi(elems.at(1)));
	if (p)
		p->moveBackward();
	p = getPlayerAt(std::stoi(elems.at(2)));
	if (p)
		p->moveBackward();
	cv_m.unlock();
}

void Client::sendMessage(std::string message)
{
	send(sock, message.c_str(), message.length(), 0);
}

void Client::createProjectile(std::string& str)
{
	cv_m.lock();
	std::vector<std::string> elems = split(str, ';');
	std::shared_ptr<Projectile> p = std::shared_ptr<Projectile>(new Projectile());
	p->position.x = std::stof(elems.at(1));
	p->position.y = std::stof(elems.at(2));
	p->position.z = std::stof(elems.at(3));
	p->orientation.x = std::stof(elems.at(4));
	p->orientation.y = std::stof(elems.at(5));
	p->orientation.z = std::stof(elems.at(6));
	p->id = std::stoi(elems.at(7));
	p->owner_id = std::stoi(elems.at(8));
	p->angleX = glm::orientedAngle(glm::vec3(1.0f, 0.0f, 0.0f), p->orientation, glm::vec3(0.0f, 0.0f, 1.0f));
	p->angleY = glm::orientedAngle(glm::vec3(0.0f, 1.0f, 0.0f), p->orientation, glm::vec3(0.0f, 0.0f, 1.0f));
	projectiles.push_back(std::shared_ptr<Projectile>(p));
	cv_m.unlock();
}

void Client::removeProjectile(std::string& str)
{
	cv_m.lock();
	std::vector<std::string> elems = split(str, ';');
	projectiles.remove_if([elems](std::shared_ptr<Projectile> p){
		return std::stoi(elems.at(2)) == p->id;
	});
	cv_m.unlock();
}

void Client::init()
{
	projectiles = std::list<std::shared_ptr<Projectile>>();
	chars = (char*)malloc(sizeof(char)* 50);
	HANDLE  hThreadArray;
	DWORD   dwThreadIdArray;
	bool end = false;
	std::string str = "";
	char* c = (char*)malloc(sizeof(char)* 50);
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(34567);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(sock, (SOCKADDR *)&sin, sizeof(sin));
	int val = connect(sock, (SOCKADDR *)&sin, sizeof(sin));
	hThreadArray = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		createThreadListenOnClient,       // thread function name
		this,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdArray
	);
}

void Client::rotate(float x, float y)
{
	cv_m.lock();
	std::shared_ptr<PlayerGL> p = getPlayerAt(selfId);
	if (p && p->doRoation(x, y))
	{
		sendMessage(std::string("R;")
			+ std::to_string(p->getOrientation().x) +
			std::string(";") + std::to_string(p->getOrientation().y) +
			std::string(";") + std::to_string(p->getOrientation().z) +
			std::string(";") + std::to_string(selfId));
	}
	cv_m.unlock();
};

void Client::fire()
{
	sendMessage(std::string("T")); // Le client envoie juste le fait qu'il tire (le serveur envoi le projectile en face de la position réélle du joueur)
}

void Client::gameLoopStep(float micro)
{
	if (players.empty())
		return;
	for each (auto p in players)
	{
		p->updatePos(micro);
	}
	for each (auto p in projectiles)
	{
		p->position += p->orientation;
	}
}

