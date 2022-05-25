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
	// 程序运行时需要输入端口号
	if (argc != 2) { 
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	// 初始化相关库与 Linux 的区别之一
	WORD ver = MAKEWORD(2, 2); // 版本号
	WSADATA dat;
	if (WSAStartup(ver, &dat) != 0) 
		ErrorHandling("WSAStartup() error!");
	
	/* -------网络编程的一系列操作--------- */
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	int szClntAddr = sizeof(clntAddr);
	char message[] = "Hello World!";
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(argv[1])); // 程序运行时输入的端口号
						// htons ---> host to net unsigned short
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error!");
	if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error!");
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error!");
	
	/* -----只剩下accept()、send()/recv()和closesocket()----- */
	int i = 0;
	while (true) {
		hClntSock = accept(hServSock, (SOCKADDR*) &clntAddr, &szClntAddr);
		if (hClntSock == INVALID_SOCKET)
			ErrorHandling("accept() error!");
		send(hClntSock, message, sizeof(message), 0);
		printf("Success Send To N0.%d Client!\n", i++);
	}
	
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;
}