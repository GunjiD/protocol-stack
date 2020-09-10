#ifndef ETHERNET_H
#define ETHERNET_H

#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define ETH_P_ALL 0x0003
#define ADDR_LEN 6

//typedef struct ethernet_hdr Eth_h;

typedef struct ETHERNET_HEADER
{
        uint8_t dest[ADDR_LEN];
        uint8_t src[ADDR_LEN];
        uint16_t ethehertype;
} ethernet_hdr;

char *dest_addr(ethernet_hdr *eth_hdr);
char *src_addr(ethernet_hdr *eth_hdr);
char *return_addr(char *address);

void eth_hdr_dbg(ethernet_hdr *eth_header, ssize_t byte);

#endif