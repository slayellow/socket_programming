#include "client.h"


int main(void)
{
	/*
	WORD --> unsigned short
	WSADATA --> Windows ���� �ʱ�ȭ ���� ���� ����ü
	SOCKADDR_IN --> sockaddr ����ü���� sa_family�� AF_INET�� ��� ����ϴ� ����ü
	*/
	WORD        wVersionRequested;
	WSADATA        wsaData;
	SOCKADDR_IN target; //Socket address information
	SOCKET      s;
	int            err;
	int            bytesSent;
	char        buf[50];
	// MAKEWORD --> 2���� �μ��� WORD�� pack�ϴ� ��ũ��
	wVersionRequested = MAKEWORD(2, 2);
	// WSAStartup --> Windows ���� �ʱ�ȭ
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		printf("WSAStartup error %ld", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	/*
	Server Address ����
	PF_INET --> �������� ü��
	AF_INET --> �ּ� ü��(IPv4���ͳ� ��������)
	inet_addr --> ���ڿ� ������ �̷���� IP ���ڿ��� long���� ���� IP�ּҷ� ��ȯ
	htons --> ,Host���� Network�� short�� �����͸� ������ ����Ʈ ������ �ٲٴ� �Լ�
	htonl --> long �� �������� ����Ʈ ������ �ٲپ��ִ� �Լ�
	*/
	target.sin_family = AF_INET; // address family Internet
	target.sin_port = htons(SERVER_PORT); //Port to connect on
	target.sin_addr.s_addr = inet_addr(IPAddress); //Target IP

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
	if (s == INVALID_SOCKET)
	{
		cout << "socket() error : " << WSAGetLastError() << endl;
		WSACleanup();
		return 0; //Couldn't create the socket
	}

	// connect --> ������ ������ ���ִ� �Լ�
	// SOCKADDR --> ������ �ּҸ� ��� �⺻ ����ü ����
	// reinterpret_cast --> ������ ������ Ÿ�Գ��� ��ȯ ���
	// ex) target ������ SOCKADDR type�� �ٲٱ�
	if (connect(s, reinterpret_cast<SOCKADDR *>(&target), sizeof(target)) == SOCKET_ERROR)
	{
		cout << "connect() error : " << WSAGetLastError() << endl;
		cout << "���� ���� �������ּ���." << endl;
		WSACleanup();
		return 0; //Couldn't connect
	}

	printf("Sending HELLO...\n");
	// send --> Ŭ���̾�Ʈ�� �޼����� �������� ����
	bytesSent = send(s, "HELLO", strlen("HELLO"), 0); // use "send" in windows

	int n;
	std::string sRand;
	int iRand;
	while (true)
	{
		// read, write�ε� ���� �ְ�ޱ� ����(Linux)
		// recv(����, ���� ������ ���� �迭�ּ�, �迭�� ũ��, flag)
		// ������ �����Ͱ� ���ٸ� ��� ������
		n = recv(s, buf, 50, 0); // read max 50 bytes
		if (n <= 0) { printf("Got nothing\n"); break; }
		buf[n] = 0; // make a string

		cout << "Received: " << buf << endl;
		sRand = buf;
		// stoi --> string ������ Ÿ���� ���������� ��ȯ
		iRand = stoi(sRand);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Sending \"" << ++iRand << "\"" << " to client" << endl;
		sRand = std::to_string(iRand);
		bytesSent = send(s, sRand.c_str(), sRand.length(), 0);
	}
	// ���� �ݱ�
	closesocket(s);
	// �Ҹ��ڿ� ���� ����
	WSACleanup();
	return 0;

}