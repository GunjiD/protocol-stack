#ifndef ETHERNET_H
#define ETHERNET_H

#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define ETH_P_ALL 0x0003
#define ADDR_LEN 6

struct ethernet_hdr;
typedef struct ethernet_hdr Eth_h;

char *dest_addr(Eth_h *eth_hdr);
char *src_addr(Eth_h *eth_hdr);

#endif