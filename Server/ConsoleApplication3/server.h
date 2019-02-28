// #define --> ���� ġȯ, ������ ���� �� ��, �Һ��� ��
// #ifndef --> ������ �Ǿ� ���� ������ �����Ѵ�.
#ifndef SERVER_MAIN_H
#define SERVER_MAIN_H

// WinSock2.h --> ������ ����ϱ� ���� �������
#include <WinSock2.h>

#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

// thread --> ������ ����� ���� ���̺귯��
// chrono --> ����и��� ������ �ð� ���� ���̺귯��
#include <thread>
#include <chrono>

#include <string>
#include <stdexcept>
#define BUF_SIZE 4096
#define SERVER_PORT 11235  // server port number


class Server
{
public:
	void CreateSocket();
	void ConnectClient();
	void Communication();
	void ErrorHandling();
	Server();
	~Server();
private:
	/*
	WORD --> unsigned short
	WSADATA --> Windows ���� �ʱ�ȭ ���� ���� ����ü
	SOCKADDR_IN --> sockaddr ����ü���� sa_family�� AF_INET�� ��� ����ϴ� ����ü
	*/
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKADDR_IN servAddr, cliAddr; //Socket address information
	SOCKET server, client;
	int            err;
	int            bytesSent;
	char        buf[BUF_SIZE];
};
#endif // !SERVER_MAIN_H