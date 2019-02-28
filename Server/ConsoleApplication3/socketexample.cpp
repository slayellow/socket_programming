#include "server.h"

int makeRand();
void Server::CreateSocket() {
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
	if (server == INVALID_SOCKET)
	{
		ErrorHandling();
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

												  // bind(����, ���� ������� ����ü�� �ּ�, ����ü�� ũ��)
												  // SOCKADDR --> ������ �ּҸ� ��� �⺻ ����ü ����
												  // reinterpret_cast --> ������ ������ Ÿ�Գ��� ��ȯ ���
												  // ex) servAddr ������ SOCKADDR type�� �ٲٱ�
	int x = bind(server, reinterpret_cast<SOCKADDR *>(&servAddr), sizeof(servAddr));
	if (x == SOCKET_ERROR)
	{
		ErrorHandling();
	}
}
void Server::ConnectClient() {
	cout << "Waiting for client..." << endl;
	// listen --> ������ ���� �����·� �������, 5 --> �ѹ��� ��û ������ �ִ� ���ӽ��� ��
	listen(server, 5);
	int xx = sizeof(cliAddr);
	// accept --> ���� ��û ����
	client = accept(server, reinterpret_cast<SOCKADDR *>(&cliAddr), &xx);
	cout << "Connection established. New socket num is " << client << endl;

}
void Server::Communication() {
	int iRand = 0;
	int n = 0;
	while (true)
	{
		// read, write�ε� ���� �ְ�ޱ� ����(Linux)
		// recv(����, ���� ������ ���� �迭�ּ�, �迭�� ũ��, flag)
		// ������ �����Ͱ� ���ٸ� ��� ������
		n = recv(client, buf, 50, 0);
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
			bytesSent = send(client, sRand.c_str(), sRand.length(), 0);

			continue;
		}
		std::string sNum(buf);
		// stoi --> string ������ Ÿ���� ���������� ��ȯ
		iRand = stoi(sNum);
		cout << "Server got " << "\"" << iRand << "\"" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Sending \"" << ++iRand << "\"" << " to client" << endl;
		auto sRand = std::to_string(iRand);
		bytesSent = send(client, sRand.c_str(), sRand.length(), 0);
	}
}
Server::Server() {
	// MAKEWORD --> 2���� �μ��� WORD�� pack�ϴ� ��ũ��
	wVersionRequested = MAKEWORD(2, 2);
	// WSAStartup --> Windows ���� �ʱ�ȭ
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		ErrorHandling();
	}
}
void Server::ErrorHandling() {
	cout << "Error : " << WSAGetLastError() << endl;
	WSACleanup();
	exit(0);
}
Server::~Server() {
	// ���� �ݱ�
	closesocket(client);
	closesocket(server);

	// �Ҹ��ڿ� ���� ����
	WSACleanup();
}
int main(void)
{
	Server serv = Server();
	serv.CreateSocket();
	serv.ConnectClient();
	serv.Communication();
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
