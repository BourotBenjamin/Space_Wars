#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <memory>



struct NetworkClient
{
	int id;
	int x;
	int y;
	int z;
	int angleX;
	int angleY;
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
	SOCKET sock;
	std::list<std::shared_ptr<NetworkClient>> clients;
	int nb_clients_all_time = 0, nb_clients = 0;
	char* chars = (char*)malloc(sizeof(char)* 15);

	static DWORD WINAPI createThreadListenOnServer(LPVOID  client);
	static DWORD WINAPI createThreadPingAllClients(LPVOID server);

	void init();
	void listenForClientsConnections(SOCKADDR_IN sin, SOCKET sock);
	int listenForMessage(std::shared_ptr<NetworkClient>  client);
	void newClientConnection(std::shared_ptr<NetworkClient> client);
	std::shared_ptr<NetworkClient> initClient(SOCKET csock);
	void removrClientFromList(std::shared_ptr<NetworkClient> c);
	void removeClientDependencies(std::shared_ptr<NetworkClient> c);

	void sendMessageToOneClient(std::shared_ptr<NetworkClient> listener, std::string message);
	void sendMessageToAllClients(std::string message);

	std::string createCoordMessage(std::shared_ptr<NetworkClient> client);
	void sendOneClientCoordToOneClient(std::shared_ptr<NetworkClient> client, std::shared_ptr<NetworkClient> listener);
	void sendAllClientsCoordToOneClient(std::shared_ptr<NetworkClient> listener);
	void sendOneClientCoordToAllClients(std::shared_ptr<NetworkClient> c);
	void sendAllClientsCoordToAllClients();
	int Server::pingAllClients();
	void Server::recivePingFromClient(std::shared_ptr<NetworkClient> c);
};

struct CoupleServerClient {
	Server* server;
	std::shared_ptr<NetworkClient> client;
};
