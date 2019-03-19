#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct ip_hdr
{

	unsigned char ip_header_len : 4;
	unsigned char ip_version : 4;
	unsigned char ip_tos;
	unsigned short ip_total_len;

	unsigned short ip_id;
	unsigned char ip_frag_offset : 5;
	unsigned char ip_morefrag : 1;
	unsigned char ip_dontfrag : 1;
	unsigned char ip_reserved : 1;
	unsigned char ip_frag_offset2;

	unsigned char ip_ttl;
	unsigned char ip_protocol;
	unsigned short ip_checksum;

	unsigned int ip_srcip;
	unsigned int ip_dstip;
}IP_HDR;

typedef struct udp_hdr {

	unsigned short udp_srcport;
	unsigned short udp_dstport;
	unsigned short udp_length;
	unsigned short udp_checksum;
}UDP_HDR;

typedef struct sc_hdr {

	unsigned short sign; // 0x 08 01
	unsigned short checksum;
	unsigned long res1;
	unsigned long res2;
	unsigned long res3;
	unsigned short command; // if 0x 00 06 = player join
	unsigned char res4[6];
	unsigned char player_num;
	unsigned char res5[19];
	IN_ADDR target_ip;
	unsigned char res6[8];
	unsigned char name[1]; // name pointer
}SC_HDR;