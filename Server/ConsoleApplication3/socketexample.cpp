#include "server.h"

int makeRand();

int main(void)
{
	/*
		WORD --> unsigned short
		WSADATA --> Windows ���� �ʱ�ȭ ���� ���� ����ü
		SOCKADDR_IN --> sockaddr ����ü���� sa_family�� AF_INET�� ��� ����ϴ� ����ü
	*/
	WORD        wVersionRequested;
	WSADATA        wsaData;
	SOCKADDR_IN servAddr, cliAddr; //Socket address information
	int            err;
	int            bytesSent;
	char        buf[50];
	// MAKEWORD --> 2���� �μ��� WORD�� pack�ϴ� ��ũ��
	wVersionRequested = MAKEWORD(2, 2);
	// WSAStartup --> Windows ���� �ʱ�ȭ
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		cout << "WSAStartup error " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}
	/*
	Server Address ����
	PF_INET --> �������� ü��
	AF_INET --> �ּ� ü��(IPv4���ͳ� ��������)
	inet_addr --> ���ڿ� ������ �̷���� IP ���ڿ��� long���� ���� IP�ּҷ� ��ȯ
	htons --> ,Host���� Network�� short�� �����͸� ������ ����Ʈ ������ �ٲٴ� �Լ�
	htonl --> long �� �������� ����Ʈ ������ �ٲپ��ִ� �Լ�
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

	// bind(����, ���� ������� ����ü�� �ּ�, ����ü�� ũ��)
	// SOCKADDR --> ������ �ּҸ� ��� �⺻ ����ü ����
	// reinterpret_cast --> ������ ������ Ÿ�Գ��� ��ȯ ���
	// ex) servAddr ������ SOCKADDR type�� �ٲٱ�
	int x = bind(s, reinterpret_cast<SOCKADDR *>(&servAddr), sizeof(servAddr));
	if (x == SOCKET_ERROR)
	{
		cout << "Binding failed. Error code: " << WSAGetLastError() << endl;
		WSACleanup();
		return false; //Couldn't connect
	}

	cout << "Waiting for client..." << endl;
	// listen --> ������ ���� �����·� �������, 5 --> �ѹ��� ��û ������ �ִ� ���ӽ��� ��
	listen(s, 5);
	int xx = sizeof(cliAddr);
	// accept --> ���� ��û ����
	SOCKET s2 = accept(s, reinterpret_cast<SOCKADDR *>(&cliAddr), &xx);
	cout << "Connection established. New socket num is " << s2 << endl;

	int iRand = 0;
	int n = 0;
	while (true)
	{
		// read, write�ε� ���� �ְ�ޱ� ����(Linux)
		// recv(����, ���� ������ ���� �迭�ּ�, �迭�� ũ��, flag)
		// ������ �����Ͱ� ���ٸ� ��� ������
		n = recv(s2, buf, 50, 0);
		if (n <= 0) { cout << "Got nothing" << endl; break; }
		buf[n] = 0;
		// strcmp --> ��Ʈ�� ��, ������ 0�� ����
		if (!strcmp(buf, "HELLO"))
		{// Initial communication
			iRand = makeRand();	// ����� ���� �Լ� ȣ��
			// auto --> ���� ����� Ư�� ���������� ����X
			// std::to_string --> ���ڸ� string���� ��ȯ
			auto sRand = std::to_string(iRand);
			cout << "Sending random number " << iRand << " to the client." << endl;
			// send --> ������ �޼����� Ŭ���̾�Ʈ ���� ����
			// c_str --> string ������ char * ������ ��ȯ
			bytesSent = send(s2, sRand.c_str(), sRand.length(), 0);

			continue;
		}
		std::string sNum(buf);
		// stoi --> string ������ Ÿ���� ���������� ��ȯ
		iRand = stoi(sNum);
		cout << "Server got " << "\"" << iRand << "\"" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Sending \"" << ++iRand << "\"" << " to client" << endl;
		auto sRand = std::to_string(iRand);
		bytesSent = send(s2, sRand.c_str(), sRand.length(), 0);
	}
	// ���� �ݱ�
	closesocket(s2);
	closesocket(s);

	// �Ҹ��ڿ� ���� ����
	WSACleanup();
	return 0;
}

int makeRand()
{
	// �õ� ����
	random_device rd;
	mt19937 rng(rd());
	// ���� ����
	uniform_int_distribution<int> ud(1, 1024);
	// �� ����
	return ud(rng);
}
