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
#include <condition_variable>
#include <thread>
#include "PlayerGL.h"
#include <glm/gtx/vector_angle.hpp>


struct Projectile
{
	unsigned short id;
	glm::vec3 position;
	glm::vec3 orientation;
	unsigned short owner_id;
	float angleX;
	float angleY;
};


class Client
{
public:
	Client();
	~Client();
	void sendMessage(std::string message);

	int getPlayerSize(){ return players.size(); }
	int getProjectileSize(){ return projectiles.size(); }
	std::list<std::shared_ptr<Projectile>>& getProj() { return projectiles; }
	std::list<std::shared_ptr<PlayerGL>>& getPlayers() { return players; }

	std::shared_ptr<PlayerGL> getPlayerAt(int index);
	int getSelfID(){ return selfId; }
	void rotate(float x, float y);
	void fire();
	void gameLoopStep(float micro);

	std::mutex cv_m; // This mutex is used for three purposes:

private:


	std::list<std::shared_ptr<PlayerGL>> players;
	std::list<std::shared_ptr<Projectile>> projectiles;
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

