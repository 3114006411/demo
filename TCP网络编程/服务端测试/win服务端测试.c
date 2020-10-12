#include<stdio.h>
#include<stdlib.h>
//#include<Windows.h>
#include<WinSock2.h>
void ErrorHandlind(const char* message);


int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET SerSock, CliSock;
	SOCKADDR_IN ServAddr,ClntAddr;
	char buf[] = "hello world";

	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandlind("WSAStartup() error");

	SerSock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAddr.sin_port = htons(atoi(argv[1]));

	bind(SerSock, (SOCKADDR*)&ServAddr, sizeof(ServAddr));

	listen(SerSock, 5);
	//printf("%d", ServAddr);

	int szClntAddr = sizeof(ClntAddr);
	CliSock=accept(SerSock, (SOCKADDR*)&ClntAddr, &szClntAddr);
	//send(CliSock, buf, sizeof(buf), 0);
	
	closesocket(CliSock);
	closesocket(SerSock);

	WSACleanup();
	return 0;
}

void ErrorHandlind(const char* message)
{
	printf("%s", message);
	exit(1);
}