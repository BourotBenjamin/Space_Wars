#include "Client.h"


Client::Client()
{
	init();
}


Client::~Client()
{
	closesocket(sock);
	WSACleanup();
}


DWORD WINAPI Client::createThreadListenOnClient(LPVOID c)
{
	return ((Client*) c)->listenForMessage();
}

int Client::listenForMessage()
{
	int size = 0;
	while (true)
	{
		size = recv(*((SOCKET*)sock), chars, 90, 0);
		if (size > 0)
		{
			std::string s(chars, chars + size);
			std::cout << s << std::endl;
		}
	}
	return 0;
}

void Client::init()
{
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

int main()
{

}