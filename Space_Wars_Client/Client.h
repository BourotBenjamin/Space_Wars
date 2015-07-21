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
#include <memory>
#include <algorithm>
#include "PlayerGL.h"


struct Projectile
{
	int id;
	glm::vec3 position;
	glm::vec3 orientation;
};


class Client
{
public:
	Client();
	~Client();
	void sendMessage(std::string message);
	std::list<PlayerGL> players;
	std::list<std::shared_ptr<Projectile>> projectiles;

	PlayerGL* getPlayerAt(int index);
	int getSelfID(){ return selfId; }
	void rotate(float x, float y);
	void fire();
	void gameLoopStep(float micro);

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
	void createProjectile(std::string& str);
	void removeProjectile(std::string& str);
	void collision(std::string& str);
};

