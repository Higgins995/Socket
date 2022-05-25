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
	/* -----只剩下send()/recv()和closesocket()----- */
	
	// 读取用户的请求命令
	
	
	// 处理请求
	
	
	// 向服务器发送请求
	send(hServSock, xxx, sizeof(xxxx) - 1, 0);
	
	// 接受服务器的返回
	strLen = recv(hServSock, message, sizeof(message) - 1, 0);
	if (strLen == -1)
		ErrorHandling("recv() error!");
	// printf("Message From Server: %s \n", message);
	
	closesocket(hServSock);
	WSACleanup();
	return 0;
}