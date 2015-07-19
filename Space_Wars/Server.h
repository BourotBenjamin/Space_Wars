#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <memory>
#include <glm\vec3.hpp>
#include <glm\geometric.hpp>
#include <time.h>
#define CLOCKS_PER_SEC = 10000;



struct NetworkClient
{
	int id;
	glm::vec3 pos;
	glm::vec3 orientation;
	SOCKET sock;
	std::string name;
	bool ping;
	int pingAttemps;
	DWORD threadId;
	HANDLE threadHandle;
	bool operator== (NetworkClient const &c)
	{
		return c.id == this->id;
	}
};

class Server
{
public:
	Server();
	~Server();
private:
	DWORD pingThreadId;
	HANDLE pingThreadHandle;
	DWORD gameLoopThreadId;
	HANDLE gameLoopThreadHandle;
	SOCKET sock;
	std::list<std::shared_ptr<NetworkClient>> clients;
	int nb_clients_all_time = 0, nb_clients = 0;
	char* chars = (char*)malloc(sizeof(char)* 15);

	static DWORD WINAPI createThreadListenOnServer(LPVOID  client);
	static DWORD WINAPI createThreadPingAllClients(LPVOID server);
	static DWORD WINAPI createGameLoop(LPVOID server);

	void init();
	void gameLoop();
	void listenForClientsConnections(SOCKADDR_IN sin, SOCKET sock);
	int listenForMessage(std::shared_ptr<NetworkClient>  client);
	void newClientConnection(std::shared_ptr<NetworkClient> client);
	std::shared_ptr<NetworkClient> initClient(SOCKET csock);
	void removeClientFromList(std::shared_ptr<NetworkClient> c);
	void removeClientDependencies(std::shared_ptr<NetworkClient> c);
	void updateRotation(std::shared_ptr<NetworkClient> c, std::string str);

	void sendMessageToOneClient(std::shared_ptr<NetworkClient> listener, std::string message);
	void sendMessageToAllClients(std::string message);

	std::string createCoordMessage(std::shared_ptr<NetworkClient> client, bool n);
	void sendOneClientCoordToOneClient(std::shared_ptr<NetworkClient> client, std::shared_ptr<NetworkClient> listener, bool n);
	void sendAllClientsCoordToOneClient(std::shared_ptr<NetworkClient> listener, bool n);
	void sendOneClientCoordToAllClients(std::shared_ptr<NetworkClient> c, bool n);
	void sendAllClientsCoordToAllClients(bool n);
	int Server::pingAllClients();
	void Server::recivePingFromClient(std::shared_ptr<NetworkClient> c);
};

struct CoupleServerClient {
	Server* server;
	std::shared_ptr<NetworkClient> client;
};
