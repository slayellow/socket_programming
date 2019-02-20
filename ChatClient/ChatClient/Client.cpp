#include <WinSock2.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <stdexcept>
#include<process.h>
#define SERVER_PORT 22001
#define SERVER_IP "127.0.0.1"
using std::cout;
using std::endl;
using std::string;
using std::cin;
void read(void*);
SOCKET client;
char readBuf[500];
int main(void)
{
	WSADATA wsa;
	SOCKADDR_IN client_addr;
	char sendBuf[500];
	int length = 0;
	int cli_size = 0;
	string s;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(SERVER_PORT);
	client_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(client, reinterpret_cast<SOCKADDR *>(&client_addr), sizeof(client_addr));
	cout << "Client Connected! " << endl;
	
	_beginthread(read, 0, (void*)1);
	while (true)
	{
		memset(sendBuf, 0, strlen(sendBuf));
		cout << "Client : ";
		cin.getline(sendBuf, 500);
		send(client, sendBuf, strlen(sendBuf), 0);
		if (!strcmp(sendBuf, "exit\n")) { break; }
	}
	closesocket(client);
	WSACleanup();
	return 0;
}
void read(void*) {
	while (true) {
		recv(client, readBuf, sizeof(readBuf), 0);
		printf("Server : %s\n", readBuf);
		readBuf[strlen(readBuf) - 1] = '\0';
		if (!strcmp(readBuf, "exit")) break;
		memset(readBuf, 0, sizeof(readBuf));
	}
}