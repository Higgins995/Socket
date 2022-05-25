#define WIN32_LEAN_AND_MEAN // 将winsock2中更新的宏定义忽略
#include <cstdio>
#include <windows.h>
#include <winsock2.h>

// 报错处理函数
void ErrorHandling(char* message) { 
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


int main(int argc, char *argv[]) {
	/* 在程序中直接写死端口
	if (argc != 2) { 
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	*/
	
	// 初始化相关库与 Linux 的区别之一
	WORD ver = MAKEWORD(2, 2); // 版本号
	WSADATA dat;
	if (WSAStartup(ver, &dat) != 0) 
		ErrorHandling("WSAStartup() error!");
	
	/* -------网络编程的一系列操作--------- */
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	int szClntAddr = sizeof(clntAddr);
	int strLen;
	char recvBuff[50], sendBuff[] = "Hello I'm Higgins";
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(1289); // 程序运行时输入的端口号
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("Socket() Error!");
	if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("Bind() Error!");
	printf("Waiting for Connecting...\n");
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("Listen() Error!");
	hClntSock = accept(hServSock, (SOCKADDR*) &clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("Accept() Error!");
	else {
		printf("Connected from %s\n", inet_ntoa(clntAddr.sin_addr));
	}
	
	/* -----只剩下send()/recv()和closesocket()----- */
	while (true) {
		// 接受客户端的请求
		printf("Wating for Client Request ....");
		strLen = recv(hClntSock, recvBuff, sizeof(recvBuff), 0);
		if (strLen > 0)
			printf("Request is: %s\n", recvBuff);
		else {
			printf("Connection Closed!\n");
			break;
		}
		
		// 处理客户端的请求
		if (strcmp(recvBuff, "getName") == 0) {
			send(hClntSock, sendBuff, sizeof(sendBuff) + 1, 0);
		} else if (strcmp(recvBuff, "getHost") == 0) {
			send(hClntSock, "https://www.Higgins.top", 24, 0);
		} else {
			send(hClntSock, "Request Error!", 16, 0);
		}
	}
	
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;
}