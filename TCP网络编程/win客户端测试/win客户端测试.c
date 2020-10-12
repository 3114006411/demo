#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

void ErrorHandling(char* message);
int main(int argc, char* argv [])
{
	WSADATA Wsadata;
	SOCKET ClntSock;
	SOCKADDR_IN ServAddr;
	char buf[30];
	int strLen;
	if (argc != 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	WSAStartup(MAKEWORD(2, 2), &Wsadata);

	ClntSock=socket(AF_INET, SOCK_STREAM, 0);
	if (ClntSock == SOCKET_ERROR)
		ErrorHandling("socket() failed");
	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(atoi(argv[2]));
	ServAddr.sin_addr.s_addr = inet_addr(argv[1]);

	if (connect(ClntSock, (SOCKADDR*)&ServAddr, sizeof(ServAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");
	




	strLen=recv(ClntSock, buf, strlen(buf) - 1, 0);
	if (strLen == -1)
		ErrorHandling("read() error");
	printf("Message from server: %s \n", buf);






	closesocket(ClntSock);
	WSACleanup();

	system("pause");
	return 0;
}

void ErrorHandling(char* message)
{
	printf("%s", message);
	exit(1);
}