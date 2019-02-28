// #define --> 값을 치환, 공통의 값이 들어갈 때, 불변의 값
// #ifndef --> 선언이 되어 있지 않으면 선언한다.
#ifndef SERVER_MAIN_H
#define SERVER_MAIN_H

// WinSock2.h --> 소켓을 사용하기 위한 헤더파일
#include <WinSock2.h>

#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

// thread --> 스레드 사용을 위한 라이브러리
// chrono --> 나노밀리초 단위로 시간 측정 라이브러리
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
	WSADATA --> Windows 소켓 초기화 정보 저장 구조체
	SOCKADDR_IN --> sockaddr 구조체에서 sa_family가 AF_INET인 경우 사용하는 구조체
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