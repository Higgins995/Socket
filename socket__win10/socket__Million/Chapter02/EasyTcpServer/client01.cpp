#define WIN32_LEAN_AND_MEAN // 将winsock2中更新的宏定义忽略
#include <iostream>
#include <windows.h>
#include <winsock2.h>

#if 0
#pragma comment(lib, "ws2_32.lib") // 静态链接ws2_32库文件
#endif

// 报错处理函数
void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

using namespace std;

int main(int argc, char *argv[]) {
	/* 直接写死网络地址和端口号
	if (argc != 3) { 
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	*/
	
	// 初始化相关库与 Linux 的区别之一
	WORD ver = MAKEWORD(2, 2); // 版本号
	WSADATA dat;
	if (WSAStartup(ver, &dat) != 0) 
		ErrorHandling("WSAStartup() error!");
	
	/* -------网络编程的一系列操作--------- */
	SOCKET hServSock;
	SOCKADDR_IN servAddr;
	int strLen;
	char message[30];
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(1289); // 服务端的端口号
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器ip
	
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error!");
	if (connect(hServSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");
	/* -----只剩下recv()和closesocket()----- */
	
	strLen = recv(hServSock, message, sizeof(message) - 1, 0);
	if (strLen == -1)
		ErrorHandling("recv() error!");
	
	printf("Message From Server: %s \n", message);
	
	closesocket(hServSock);
	WSACleanup();
	return 0;
}