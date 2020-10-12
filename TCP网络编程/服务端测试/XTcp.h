#pragma once


class XTcp
{
public:
	XTcp();
	virtual ~XTcp();
	int CreateSocket();
	bool Bind(unsigned short port=9190);
	XTcp Accept();
	void Close();
	int Recv(char* buf, int bufsize);
	int Send(char* buf, int bufsize);

	char * ip;
	unsigned int sock = 0;
	unsigned short port = 0;
	static int first;
};

