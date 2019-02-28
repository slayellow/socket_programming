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
	WSADATA --> Windows 소켓 초기화 정보 저장 구조체
	SOCKADDR_IN --> sockaddr 구조체에서 sa_family가 AF_INET인 경우 사용하는 구조체
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