#include "server.h"

int makeRand();

int main(void)
{
	/*
		WORD --> unsigned short
		WSADATA --> Windows 소켓 초기화 정보 저장 구조체
		SOCKADDR_IN --> sockaddr 구조체에서 sa_family가 AF_INET인 경우 사용하는 구조체
	*/
	WORD        wVersionRequested;
	WSADATA        wsaData;
	SOCKADDR_IN servAddr, cliAddr; //Socket address information
	int            err;
	int            bytesSent;
	char        buf[50];
	// MAKEWORD --> 2개의 인수를 WORD로 pack하는 매크로
	wVersionRequested = MAKEWORD(2, 2);
	// WSAStartup --> Windows 소켓 초기화
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		cout << "WSAStartup error " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}
	/*
	Server Address 정보
	PF_INET --> 프로토콜 체계
	AF_INET --> 주소 체계(IPv4인터넷 프로토콜)
	inet_addr --> 숫자와 점으로 이루어진 IP 문자열을 long형의 숫자 IP주소로 변환
	htons --> ,Host에서 Network로 short형 데이터를 보낼때 바이트 오더를 바꾸는 함수
	htonl --> long 형 데이터의 바이트 오더를 바꾸어주는 함수
	*/
	servAddr.sin_family = AF_INET; // address family Internet
	servAddr.sin_port = htons(SERVER_PORT); //Port to connect on
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //Target IP

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
	if (s == INVALID_SOCKET)
	{
		cout << "Socket error " << WSAGetLastError() << endl;
		WSACleanup();
		return false; //Couldn't create the socket
	}

	// bind(소켓, 소켓 구성요소 구조체의 주소, 구조체의 크기)
	// SOCKADDR --> 소켓의 주소를 담는 기본 구조체 역할
	// reinterpret_cast --> 임의의 포인터 타입끼리 변환 허용
	// ex) servAddr 변수를 SOCKADDR type로 바꾸기
	int x = bind(s, reinterpret_cast<SOCKADDR *>(&servAddr), sizeof(servAddr));
	if (x == SOCKET_ERROR)
	{
		cout << "Binding failed. Error code: " << WSAGetLastError() << endl;
		WSACleanup();
		return false; //Couldn't connect
	}

	cout << "Waiting for client..." << endl;
	// listen --> 소켓을 접속 대기상태로 만들어줌, 5 --> 한번에 요청 가능한 최대 접속승인 수
	listen(s, 5);
	int xx = sizeof(cliAddr);
	// accept --> 접속 요청 수락
	SOCKET s2 = accept(s, reinterpret_cast<SOCKADDR *>(&cliAddr), &xx);
	cout << "Connection established. New socket num is " << s2 << endl;

	int iRand = 0;
	int n = 0;
	while (true)
	{
		// read, write로도 정보 주고받기 가능(Linux)
		// recv(소켓, 수신 정보를 담을 배열주소, 배열의 크기, flag)
		// 보내준 데이터가 없다면 계속 대기상태
		n = recv(s2, buf, 50, 0);
		if (n <= 0) { cout << "Got nothing" << endl; break; }
		buf[n] = 0;
		// strcmp --> 스트링 비교, 같으면 0이 나옴
		if (!strcmp(buf, "HELLO"))
		{// Initial communication
			iRand = makeRand();	// 사용자 정의 함수 호출
			// auto --> 변수 선언시 특정 데이터형을 지정X
			// std::to_string --> 인자를 string으로 변환
			auto sRand = std::to_string(iRand);
			cout << "Sending random number " << iRand << " to the client." << endl;
			// send --> 서버가 메세지를 클라이언트 측에 전달
			// c_str --> string 변수를 char * 형으로 변환
			bytesSent = send(s2, sRand.c_str(), sRand.length(), 0);

			continue;
		}
		std::string sNum(buf);
		// stoi --> string 데이터 타입을 정수형으로 변환
		iRand = stoi(sNum);
		cout << "Server got " << "\"" << iRand << "\"" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Sending \"" << ++iRand << "\"" << " to client" << endl;
		auto sRand = std::to_string(iRand);
		bytesSent = send(s2, sRand.c_str(), sRand.length(), 0);
	}
	// 소켓 닫기
	closesocket(s2);
	closesocket(s);

	// 소멸자와 같은 개념
	WSACleanup();
	return 0;
}

int makeRand()
{
	// 시드 설정
	random_device rd;
	mt19937 rng(rd());
	// 분포 설정
	uniform_int_distribution<int> ud(1, 1024);
	// 값 추출
	return ud(rng);
}
