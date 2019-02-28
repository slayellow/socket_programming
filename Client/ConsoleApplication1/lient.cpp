#include "client.h"

Client::Client() {
	// MAKEWORD --> 2개의 인수를 WORD로 pack하는 매크로
	wVersionRequested = MAKEWORD(2, 2);
	// WSAStartup --> Windows 소켓 초기화
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		printf("WSAStartup error %ld", WSAGetLastError());
		WSACleanup();
		exit(0);
	}
}
Client::~Client() {
	// 소켓 닫기
	closesocket(client);
	// 소멸자와 같은 개념
	WSACleanup();
}
void Client::ErrorHandling() {
	cout << "Error : " << WSAGetLastError() << endl;
	WSACleanup();
	exit(0);
}
void Client::CreateSocket() {
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
	if (client == INVALID_SOCKET)
	{
		ErrorHandling();
	}
}
void Client::ConnectServer() {
	/*
	Server Address 정보
	PF_INET --> 프로토콜 체계
	AF_INET --> 주소 체계(IPv4인터넷 프로토콜)
	inet_addr --> 숫자와 점으로 이루어진 IP 문자열을 long형의 숫자 IP주소로 변환
	htons --> ,Host에서 Network로 short형 데이터를 보낼때 바이트 오더를 바꾸는 함수
	htonl --> long 형 데이터의 바이트 오더를 바꾸어주는 함수
	*/
	target.sin_family = AF_INET; // address family Internet
	target.sin_port = htons(SERVER_PORT); //Port to connect on
	target.sin_addr.s_addr = inet_addr(IPAddress); //Target IP

	// connect --> 서버와 연결을 해주는 함수
	// SOCKADDR --> 소켓의 주소를 담는 기본 구조체 역할
	// reinterpret_cast --> 임의의 포인터 타입끼리 변환 허용
	// ex) target 변수를 SOCKADDR type로 바꾸기
	if (connect(client, reinterpret_cast<SOCKADDR *>(&target), sizeof(target)) == SOCKET_ERROR)
	{
		ErrorHandling();
	}
}
void Client::Communication() {
	std::string sRand;
	int iRand;
	int n;
	printf("Sending HELLO...\n");
	// send --> 클라이언트가 메세지를 서버측에 전달
	bytesSent = send(client, "HELLO", strlen("HELLO"), 0); // use "send" in windows
	while (true)
	{
		// read, write로도 정보 주고받기 가능(Linux)
		// recv(소켓, 수신 정보를 담을 배열주소, 배열의 크기, flag)
		// 보내준 데이터가 없다면 계속 대기상태
		n = recv(client, buf, 50, 0); // read max 50 bytes
		if (n <= 0) { printf("Got nothing\n"); return; }
		buf[n] = 0; // make a string
		cout << "Received: " << buf << endl;
		sRand = buf;
		// stoi --> string 데이터 타입을 정수형으로 변환
		iRand = stoi(sRand);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Sending \"" << ++iRand << "\"" << " to client" << endl;
		sRand = std::to_string(iRand);
		bytesSent = send(client, sRand.c_str(), sRand.length(), 0);
	}
}
int main(void)
{
	Client cli = Client();
	cli.CreateSocket();
	cli.ConnectServer();
	cli.Communication();





	return 0;

}