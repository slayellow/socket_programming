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

#endif // !CLIENT_MAIN_H