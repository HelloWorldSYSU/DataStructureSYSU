#include <iostream>
#include <string> 
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		cout << "初始化失败" << endl;
		return 0;
	}
	SOCKET server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (server == INVALID_SOCKET) {
		cout << "初始化socket失败" << endl;
		return 0;
	}
	
	SOCKADDR_IN client;
	client.sin_family = AF_INET;
	client.sin_port = htons(8719);
	client.sin_addr.S_un.S_addr = inet_addr("192.168.199.");
	//char msg[] = "XiaoMiaDaLao NB";
	for (int i = 1; i <= 100; i++) {
		string str = to_string(i);
		sendto(server, str.c_str(), str.length(), 0, (sockaddr*)&client, sizeof(client));
	}
	closesocket(server);
	WSACleanup();
}
