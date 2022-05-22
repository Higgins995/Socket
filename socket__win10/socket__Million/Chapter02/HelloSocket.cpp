#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <WinSock2.h>
// #pragma comment(lib, "ws2_32.lib") // 静态链接ws2_32库文件

using namespace std;

int main(int argc, char *argv[]) {
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	
	WSAStartup(ver, &dat);
	
	WSACleanup();
	return 0;
}