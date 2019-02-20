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

#define SERVER_PORT 11235  // server port number

#endif // !SERVER_MAIN_H