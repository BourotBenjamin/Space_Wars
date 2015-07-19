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
	std::vector<std::string> elems = split(str, '-');
	PlayerGL p;
	p.setId(std::stoi(elems.at(1)));
	p.setPos(std::stof(elems.at(2)), std::stof(elems.at(3)), std::stof(elems.at(4)));
	p.setAngleX(std::stof(elems.at(5)));
	p.setAngleY(std::stof(elems.at(6)));
	players.push_back(p);
}

PlayerGL* Client::getPlayerAt(int index)
{
	for (auto it = players.begin(); it != players.end(); ++it)
	{
		if ((*it).getId() == index)
			return &(*it);
	}
	return nullptr;
}

void Client::updatePlayer(std::string& str)
{
	std::vector<std::string> elems = split(str, '-');
	PlayerGL* p = getPlayerAt(std::stoi(elems.at(1)));

	p->setId(std::stoi(elems.at(1)));
	p->setPos(std::stof(elems.at(2)), std::stof(elems.at(3)), std::stof(elems.at(4)));
	p->setAngleX(std::stof(elems.at(5)));
	p->setAngleY(std::stof(elems.at(6)));
}

void Client::removePlayer(std::string& str)
{
	std::vector<std::string> elems = split(str, '-');
	PlayerGL p;
	p.setId( std::stoi(elems.at(1)));
	players.remove(p);
}

Client::Client()
{
	init();
}


Client::~Client()
{
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
			case 'T':
				//TODO Fire
				break;
			case 'Y':
				std::vector<std::string> elems = split(s, '-');
				selfId = std::stoi(elems.at(1));
				break;
			}
			std::cout << s << std::endl;
		}
	}
	return 0;
}

void Client::sendMessage(std::string message)
{
	send(sock, message.c_str(), message.length(), 0);
}

void Client::init()
{
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

void Client::fire()
{
	PlayerGL* p = getPlayerAt(selfId);
	sendMessage(std::string("T-") + std::to_string(p->getPos().x) +
		std::string("-") + std::to_string(p->getPos().y) +
		std::string("-") + std::to_string(p->getPos().z) +
		std::string("-") + std::to_string(p->getOrientation().x) +
		std::string("-") + std::to_string(p->getOrientation().y) +
		std::string("-") + std::to_string(p->getOrientation().z) +
		std::string("-") + std::to_string(selfId));
}

void Client::move()
{
	PlayerGL* p = getPlayerAt(selfId);
	sendMessage(std::string("R-")+
		std::string("-") + std::to_string(p->getOrientation().x) +
		std::string("-") + std::to_string(p->getOrientation().y) +
		std::string("-") + std::to_string(p->getOrientation().z) +
		std::string("-") + std::to_string(selfId));
}

