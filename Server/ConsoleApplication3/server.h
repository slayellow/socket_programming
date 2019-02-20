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

#define SERVER_PORT 11235  // server port number

#endif // !SERVER_MAIN_H