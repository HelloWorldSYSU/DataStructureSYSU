#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

#define BUFLEN 512  //Max length of buffer
#define PORT 8719   //The port on which to listen for incoming data
#define PACKET_NUM 100


int main() {
	// 初始化call
	WSADATA WSAData;
	char receBuf[BUFLEN];
	char Response[] = "";
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
		printf("初始化失败");
		exit(1);
	}

	// 初始化一个UDP socket, 其中sock_dgram指定了监听的类型是UDP
	SOCKET sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockServer == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		return 0;
	}

	SOCKADDR_IN addr_Server; //服务器的地址等信息
	addr_Server.sin_family = AF_INET;
	addr_Server.sin_port = htons(PORT);
	addr_Server.sin_addr.S_un.S_addr = INADDR_ANY;
	// addr_Server.sin_addr.s_addr = inet_addr(localIP);

	// 把socket绑定在相应的地址上
	if (bind(sockServer, (SOCKADDR*)&addr_Server, sizeof(addr_Server)) == SOCKET_ERROR) {//服务器与本地地址绑定
		printf("Failed socket() %d \n", WSAGetLastError());
		return 0;
	}
	printf("Binding to socket successfully! Waiting for udp connection....\n");
	SOCKADDR_IN sender_addr;
	int sender_size = sizeof(sender_addr);
	int res_size = 0;
	int packet_cnt = 0;
	int src_pck_idx = 1;
	int pre_src_idx = 1;
	boolean done = 0;
	while (1) {
		res_size = recvfrom(sockServer, receBuf, BUFLEN, 0, (SOCKADDR*)&sender_addr, &sender_size);
		if (res_size > 0) {
			sscanf(receBuf, "%d", &src_pck_idx);;
			packet_cnt++;
			for (int i = pre_src_idx + 1; i < src_pck_idx; i++) {
				printf("Warning: # %d packet drop!!! \n", i);
			}
			printf("Receive %d packets from source.\nCurrent source packet number is %d.\n", packet_cnt, src_pck_idx);
			pre_src_idx = src_pck_idx;
		}
		else if (res_size == 0) {
			printf("closing .. \n");
		}
		else {
			printf("error occur\n");
		}
	}
}
