#pragma once
#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")


struct Player {
	int id;
	int x;
	int y;
	int z;
	int angleX;
	int angleY;
	std::string name;
	bool operator== (Player const &p)
	{
		return p.id == this->id;
	}
};

class Client
{
public:
	Client();
	~Client();
	void sendMessage(std::string message);
	std::list<Player> players;
private:
	char* chars;
	SOCKET sock;

	static DWORD WINAPI Client::createThreadListenOnClient(LPVOID c);

	void init();
	int listenForMessage();
	void removePlayer(std::string& str);
	void createPlayer(std::string& str);
};

