#pragma once
#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class Client
{
public:
	Client();
	~Client();
private:
	char* chars = (char*)malloc(sizeof(char)* 50);
	SOCKET sock;

	static DWORD WINAPI Client::createThreadListenOnClient(LPVOID c);

	void init();
	int listenForMessage();
};

