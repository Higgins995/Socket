// 单进程多任务 hello 服务器
// 2021/09/20
// 18:28
// higgins995
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;

	char message[] = "Hello, World!";

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1) error_handling("socket() error!");
	
	// 实例化保存 网络信息 的结构体变量
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error!");

	if (listen(serv_sock, 5) == -1) error_handling("listen() error!");

	clnt_addr_size = sizeof(clnt_addr);

	while (1) {
		clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
		if (clnt_sock == -1) error_handling("accept() error!");

		write(clnt_sock, message, sizeof(message));
		close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}

void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
