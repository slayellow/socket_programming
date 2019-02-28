#include "client.h"

Client::Client() {
	// MAKEWORD --> 2���� �μ��� WORD�� pack�ϴ� ��ũ��
	wVersionRequested = MAKEWORD(2, 2);
	// WSAStartup --> Windows ���� �ʱ�ȭ
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		printf("WSAStartup error %ld", WSAGetLastError());
		WSACleanup();
		exit(0);
	}
}
Client::~Client() {
	// ���� �ݱ�
	closesocket(client);
	// �Ҹ��ڿ� ���� ����
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

	// connect --> ������ ������ ���ִ� �Լ�
	// SOCKADDR --> ������ �ּҸ� ��� �⺻ ����ü ����
	// reinterpret_cast --> ������ ������ Ÿ�Գ��� ��ȯ ���
	// ex) target ������ SOCKADDR type�� �ٲٱ�
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
	// send --> Ŭ���̾�Ʈ�� �޼����� �������� ����
	bytesSent = send(client, "HELLO", strlen("HELLO"), 0); // use "send" in windows
	while (true)
	{
		// read, write�ε� ���� �ְ�ޱ� ����(Linux)
		// recv(����, ���� ������ ���� �迭�ּ�, �迭�� ũ��, flag)
		// ������ �����Ͱ� ���ٸ� ��� ������
		n = recv(client, buf, 50, 0); // read max 50 bytes
		if (n <= 0) { printf("Got nothing\n"); return; }
		buf[n] = 0; // make a string
		cout << "Received: " << buf << endl;
		sRand = buf;
		// stoi --> string ������ Ÿ���� ���������� ��ȯ
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