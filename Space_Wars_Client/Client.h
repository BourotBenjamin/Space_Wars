#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS // to use inet_ntoa
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <glm\vec3.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "PlayerGL.h"




class Client
{
public:
	Client();
	~Client();
	void sendMessage(std::string message);
	std::list<PlayerGL> players;

	PlayerGL* getPlayerAt(int index);
	int getSelfID(){ return selfId; }
	void addAngles(float x, float y)
	{ 
		PlayerGL * p = getPlayerAt(selfId);
		p->setAngleX(x);
		p->setAngleY(y);

	};
	void fire();
	void move();

private:
	char* chars;
	SOCKET sock;

	int selfId;

	static DWORD WINAPI Client::createThreadListenOnClient(LPVOID c);

	void init();
	int listenForMessage();
	void removePlayer(std::string& str);
	void createPlayer(std::string& str);
	void updatePlayer(std::string& str);
};

