#include <WinSock2.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <stdexcept>
#include <process.h>
#include <conio.h>
#define SERVER_PORT 22001
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
	SOCKADDR_IN server_addr, client_addr;
	char sendBuf[500];
	int length = 0;
	int cli_size = 0;
	string s;

	WSAStartup(MAKEWORD(2, 2), &wsa);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bind(server, reinterpret_cast<SOCKADDR *>(&server_addr), sizeof(server_addr));
	cout << "Waiting for Client....." << endl;
	
	listen(server, 5);
	cli_size = sizeof(client_addr);

	client = accept(server, reinterpret_cast<SOCKADDR *>(&client_addr), &cli_size);
	cout << "Client Connected! " << endl;

	_beginthread(read, 0, (void*)1);
	while (true)
	{
		memset(sendBuf, 0, sizeof(sendBuf));
		cout << "Server : ";
		cin.getline(sendBuf, 500);
		send(client, sendBuf, strlen(sendBuf), 0);
		if (!strcmp(sendBuf, "exit\n")) { break; }
	}
	closesocket(client);
	closesocket(server);

	WSACleanup();
	return 0;
}

void read(void*) {
	while (true) {
		recv(client, readBuf, sizeof(readBuf), 0);
		printf("Client : %s\n", readBuf);
		readBuf[strlen(readBuf) - 1] = '\0';
		if (!strcmp(readBuf, "exit")) break;
		memset(readBuf, 0, sizeof(readBuf));
	}
}