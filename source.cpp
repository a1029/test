#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mstcpip.h>
#include <process.h>

#include "util.h" 
#include "protocols.h"
#include "ip2home.h"
#pragma comment(lib, "ws2_32.lib")

#define REFRESH 25
typedef struct _user_information 
{
	char flag;
	char player_num;
	IN_ADDR player_ip;
	char ipaddr_txt[16];
	char name[50];
	char home_addr[128];
}USER_INFO;

IN_ADDR My_IP;
IN_ADDR Location_Server;
CRITICAL_SECTION cs;
USER_INFO user[256];

unsigned int __stdcall __thread_gethome(void *temp)
{
	USER_INFO X = *(USER_INFO*)temp;
	int i = X.player_num - 1; // use index;
	int err;

	if (user[i].flag) // if ready state
	{
		if (user[i].player_num == 0) return 0;

		memset(user[i].home_addr, 0, sizeof(user[0].home_addr));
		err = IP_Location(Location_Server, user[i].player_ip, user[i].home_addr, &cs);
		if (err == -1)
		{
			exit(-1);
		}

		user[i].flag = 0; //standby
	}

	return 0;
}

unsigned int __stdcall thread_checker(void *temp)
{
	while (1)
	{
		EnterCriticalSection(&cs);

		for (int i = 0; i < 256; i++)
		{
			if (user[i].flag) // if ready state
			{
				if (user[i].player_num == 0) break;
				_beginthreadex(NULL, NULL, __thread_gethome, &user[i], NULL, NULL);
			}
		}

		LeaveCriticalSection(&cs);
		Sleep(1500); // 1.5sex
	}
}
int main() 
{
	unsigned long long tcp = 0, udp = 0, icmp = 0, packets = 0;
	int Error;
	int rx;
	char rx_buffer[65535];

	WSADATA wsa;
	SOCKET s;
	SOCKADDR_IN bindsock = { 0, };

	DWORD enable = 1;

	IP_HDR* proto_ip = (IP_HDR*)rx_buffer;
	UDP_HDR* proto_udp = (UDP_HDR*)rx_buffer + sizeof(IP_HDR);
	SC_HDR* proto_sc = (SC_HDR*)rx_buffer + sizeof(IP_HDR) + sizeof(UDP_HDR);

	memset(user, 0, sizeof(user)); 
	WSAStartup(MAKEWORD(2, 2), &wsa);
	InitializeCriticalSection(&cs);
	Location_Server = Get_Location_Server();

	s = socket(AF_INET, SOCK_RAW, NULL); if (s == INVALID_SOCKET) { printf("socket() err : %d\n", WSAGetLastError());getchar(); return -1; }
	setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char*)&enable, sizeof(DWORD));
	bindsock.sin_family = AF_INET;
	bindsock.sin_port = htons(0);
	bindsock.sin_addr = My_IP = Get_My_IP();

	bind(s, (SOCKADDR*)&bindsock, sizeof(SOCKADDR));
	Error = Promisc_Socket(s); if (Error){ printf("WSAIoctol() err : %d", WSAGetLastError()); getchar(); return -1; }

	_beginthreadex(NULL, NULL, thread_checker, NULL, NULL, NULL);
	while (1)
	{
		//memset(rx_buffer, 0, sizeof(rx_buffer));
		rx = recvfrom(s, rx_buffer, sizeof(rx_buffer), NULL, NULL, NULL);
		if (rx < 0) 
		{
			printf("Recv Error : %d\n", WSAGetLastError());
			getchar();
			return -1;
		}

		switch (proto_ip->ip_protocol)
		{
			unsigned long temp;

		case IPPROTO_UDP:
			if (proto_udp->udp_dstport == htons(6112)) 
			{
				if (proto_sc->sign == htons(0x0801))
				{
					if (proto_sc->command == htons(0x0006)) //correct
					{
						temp = *(unsigned long*)&proto_sc->target_ip;
						if (temp == 0) // master
						{
							EnterCriticalSection(&cs);
							user[proto_sc->player_num].player_ip.s_addr = NULL; // tip
							user[proto_sc->player_num].player_num = proto_sc->player_num + 1; // pn
							sprintf_s(user[proto_sc->player_num].name, "%s", proto_sc->name); // pname
							user[proto_sc->player_num].flag = 0; // standby;
							//user[proto_sc->player_num].home_addr; // standby 
							LeaveCriticalSection(&cs);
							packets = REFRESH;
						}

						if (temp) // generic
						{
							EnterCriticalSection(&cs);
							memset(&user[proto_sc->player_num], NULL, sizeof(user[0])); // init
							user[proto_sc->player_num].player_ip = proto_sc->target_ip; // tip
							user[proto_sc->player_num].player_num = proto_sc->player_num; // pn
							sprintf_s(user[proto_sc->player_num].name, "%s", proto_sc->name); // pname
							user[proto_sc->player_num].flag = 1; // ready
							LeaveCriticalSection(&cs);
							packets = REFRESH;
						}
					}

					if (proto_udp->udp_srcport == htons(6112)) // udp hole punching
					{
						if (proto_ip->ip_dstip != *(unsigned int*)&My_IP) // pp~
						{
							temp = *(unsigned long*)&proto_ip->ip_dstip;
							EnterCriticalSection(&cs);
							for (int i = 0; i < 12; i++)
							{
								if (user[i].player_ip.s_addr == temp)
								{
									temp = 0;
									break; 
								}
							}

							for (int i = 126; i < 133; i++)
							{
								if (user[i].player_ip.s_addr == temp)
								{
									temp = 0;
									break;
								}
							}
							if (temp) // not NULL
							{
								user[0].player_ip.s_addr = temp;
								user[0].flag = 1; // ready
							}
							LeaveCriticalSection(&cs);
						}
						packets = REFRESH;
					}
				}
			}
			udp++;
			temp = 0;
			break;
		case IPPROTO_ICMP:
			icmp++;
			break;
		case IPPROTO_TCP:
			tcp++;
			break;
		}

		//print result

		if (packets % REFRESH == 0)
		{
			mvxy(0, 0);
			printf("TCP : %-8d UDP : %-8d ICMP : %-8d\n\n\n", tcp, udp, icmp);

			EnterCriticalSection(&cs);

			for (int i = 0; i < 8; i++)
			{
				if (!user[i].player_num) // NULL player
				{
					printf("\n\n"); // skip
					continue;
				}

				printf("%d. %-16s : %-16s (%d)\t\n", user[i].player_num, user[i].name, inet_ntoa(user[i].player_ip), user[i].flag);
				printf("    -> %-64s\n", user[i].home_addr);
			}

			printf("\n\n"); // observer

			for (int i = 126; i < 132; i++)
			{
				if (!user[i].player_num) // NULL player
				{
					printf("\n\n"); // skip		
					continue;
				}
			
				printf("%d. %-16s : %-16s (%d)\t\n", user[i].player_num, user[i].name, inet_ntoa(user[i].player_ip), user[i].flag);
				printf("    -> %-64s\n", user[i].home_addr);
			}
			LeaveCriticalSection(&cs);
		} 
		packets++;
	}
	getchar(); 
	DeleteCriticalSection(&cs);
	WSACleanup();
	
	return 0;
}