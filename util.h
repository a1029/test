#pragma once

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>

IN_ADDR Get_My_IP()
{

	HOSTENT* h;
	IN_ADDR ip;
	char hostname[256];

	gethostname(hostname, sizeof(hostname));
	h = gethostbyname(hostname);
	ip = *(IN_ADDR*)h->h_addr_list[0];

	return ip;
}

int Promisc_Socket(SOCKET s)
{
	DWORD enable = 1;
	DWORD dwWrite;
	return WSAIoctl(s, SIO_RCVALL, (int*)&enable, sizeof(enable), 0, 0, &dwWrite, 0, 0);
}
 
void mvxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return;
}

char *memstr(char* data, char* find, int datasize) {

	char *p;
	int range = strlen(find);

	for (p = data; p <= (data - range + datasize); p++) {
		if (memcmp(p, find, range) == 0) {
			return p;
		}
	}

	return 0;
}
