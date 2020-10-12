#include "XTcp.h"
#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include<Windows.h>
XTcp::XTcp()
{
#ifdef WIN32
	first = 1;
	if (first)
		first = 0;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif



}

int XTcp::CreateSocket()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	return sock;
}

bool XTcp::Bind(unsigned short port)
{
	if (sock < 0)
		CreateSocket();
	SOCKADDR_IN ServAddr;
	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServAddr.sin_port = htons(port);

	if (bind(sock, (SOCKADDR*)&ServAddr, sizeof(ServAddr)) != 0)
	{
		printf("bind port %d failed!\n", port);
		return false;
	}
	listen(sock, 5);

	return true;
}

XTcp XTcp::Accept()
{
	XTcp tcp;
	sockaddr_in caddr;
	int len = sizeof(caddr);

	int client = accept(sock, (sockaddr*)&caddr, &len);
	tcp.ip = inet_ntoa(caddr.sin_addr);
	tcp.port = ntohs(caddr.sin_port);
	tcp.sock = client;

	printf("client ip is %s,port is %d\n", &tcp.ip, &tcp.port);

	return tcp;
}

void XTcp::Close()
{
	if (socket < 0) return;
	closesocket(sock);
}

int XTcp::Recv(char* buf, int bufsize)
{

	return recv(sock,buf,bufsize,0);
}

int XTcp::Send(char* buf, int bufsize)
{
	int s = 0;
	while (s != bufsize)
	{
		int len = send(sock, buf+s, bufsize-s, 0);
		if (len <= 0) break;
		s += len;
	}
	return s;
}
