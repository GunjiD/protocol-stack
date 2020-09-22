#ifndef ETHERNET_H
#define ETHERNET_H

#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define ETH_P_ALL 0x0003
#define MAC_LEN 6

#define ETH_T_ARP 0x0806

//typedef struct ethernet_hdr Eth_h;

typedef struct ETHERNET_HEADER
{
        uint8_t dest[MAC_LEN];
        uint8_t src[MAC_LEN];
        uint16_t ethehertype;
} ethernet_hdr;

char *dest_addr(ethernet_hdr *eth_hdr);
char *src_addr(ethernet_hdr *eth_hdr);
char *return_addr(char *address);

void eth_hdr_dbg(ethernet_hdr *eth_header, ssize_t byte);

#endif