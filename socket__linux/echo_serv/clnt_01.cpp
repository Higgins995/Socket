// 单连接 回声服务器
// higgins995
// 2021/09/21
// 20:19
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]) {
	int sock;
	char message[BUF_SIZE];
	struct sockaddr_in serv_addr;
	int str_len;

	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) error_handling("sock() error!");

	// 初始化 存有网络信息的结构体变量
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error!");
	else 
		printf("Connected......\n");

	// 回声,持续性
	while (1) { 
		fgets(message, BUF_SIZE, stdin);

		write(sock, message, strlen(message));
		
		str_len = read(sock, message, BUF_SIZE - 1);
		if (str_len == -1) error_handling("read() error!");

		printf("Message from serv : %s", message);
	}
	
	close(sock);
	return 0;
}

void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
