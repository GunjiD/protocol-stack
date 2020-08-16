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

typedef struct ethernet_hdr
{
        uint8_t dest[ADDR_LEN];
        uint8_t src[ADDR_LEN];
        uint16_t ethehertype;
} Eth_h;

char *dest_addr(Eth_h *eth_hdr);
char *src_addr(Eth_h *eth_hdr);
char *return_addr(char *address);

void eth_hdr_dbg(struct ethernet_hdr *eth_header, ssize_t byte);

#endif