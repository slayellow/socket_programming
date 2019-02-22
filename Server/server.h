#ifndef SERVER_MAIN_H
#define SERVER_MAIN_H
#include <iostream>
#include <string.h>
#include "stdlib.h"
#include "sys/types.h"
#include "netinet/in.h"
#include <fstream>
#include "arpa/inet.h"
#include "unistd.h"
#include "sys/socket.h"
using std::cout;
using std::endl;

typedef unsigned long DWORD;
#define SERVER_PORT 10000
#define MAXBUF 8192 * 10
#define m_BandWidth 0.1

#include <sys/time.h>

class Server
{
	public:
		Server();
		~Server();
		void CreateSocket();
		void ConnectClient();
		void SendPacket();

	private:
		int cli_size;
		struct sockaddr_in server_addr, client_addr;
		int server, client;	
		int server_len;
		char sendbuf[MAXBUF];
		char recvbuf[MAXBUF];
		DWORD dwStartTicks, dwEndTicks, time;
		unsigned int fileSize, sendedSize;
		int ret, sendSize;
		double m_Speed;
};

#endif
