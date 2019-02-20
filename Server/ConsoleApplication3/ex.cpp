/*
#include <iostream>
#include <WinSock2.h>
using namespace std;

void main() {
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult == INVALID_SOCKET) {
		cout << "ERROR : " << iResult << endl;
		WSACleanup();
		return;
	}
	WSACleanup();
}
*/