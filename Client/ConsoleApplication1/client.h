#ifndef CLIENT_MAIN_H
#define CLIENT_MAIN_H

#include <WinSock2.h>

#include <iostream>
using std::cout;
using std::endl;

#include <thread>
#include <chrono>

#include <string>
#include <stdexcept>

#define SERVER_PORT 11235  // server port number
#define BUF_SIZE 4096 // block transfer size  
#define QUEUE_SIZE 10
#define IPAddress "127.0.0.1" // server IP address

class Client
{
public:
	void CreateSocket();
	void ConnectServer();
	void Communication();
	void ErrorHandling();
	Client();
	~Client();
private:
	/*
	WORD --> unsigned short
	WSADATA --> Windows ���� �ʱ�ȭ ���� ���� ����ü
	SOCKADDR_IN --> sockaddr ����ü���� sa_family�� AF_INET�� ��� ����ϴ� ����ü
	*/
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKADDR_IN target; // Server Address Infomation
	SOCKET client;
	int            err;
	int            bytesSent;
	char        buf[BUF_SIZE];
};
#endif // !CLIENT_MAIN_H