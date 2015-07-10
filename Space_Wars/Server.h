#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <string>
#include <list>



struct NetworkClient
{
	int id, x, y, angle;
	SOCKET sock;
	std::string name;
	bool operator== (NetworkClient const &c)
	{
		return c.id == this->id;
	}
};

class Server
{
public:
	void init();
	Server();
	~Server();
private:
	SOCKET sock;
	std::list<NetworkClient> clients;
	int nb_clients_all_time = 0, nb_clients = 0;
	char* chars = (char*)malloc(sizeof(char)* 15);

	static DWORD WINAPI Server::createThreadListenOnServer(LPVOID  client);

	void listenForClientsConnections(SOCKADDR_IN sin, SOCKET sock);
	int listenForMessage(NetworkClient*  client);
	void newClientConnection(NetworkClient* client);
	NetworkClient& initClient(SOCKET csock);
	void Server::removeClient(NetworkClient* c);

	void sendMessageToOneClient(NetworkClient* listener, std::string message);
	void sendMessageToAllClients(std::string message);

	std::string createCoordMessage(NetworkClient* client);
	void sendOneClientCoordToOneClient(NetworkClient* client, NetworkClient* listener);
	void sendAllClientsCoordToOneClient(NetworkClient* listener);
	void sendOneClientCoordToAllClients(NetworkClient* c);
	void sendAllClientsCoordToAllClients();
};

struct CoupleServerClient {
	Server* server;
	NetworkClient* client;
};
