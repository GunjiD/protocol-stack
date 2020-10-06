#ifndef BYTE_ORDER_H
#define BYTE_ORDER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ip.h"


int host_byte_order(void);
uint16_t byte_swap16(uint16_t x);
uint32_t byte_swap32(uint32_t x);
uint16_t packet_ntohs(uint16_t network_short);
uint32_t packet_ntohl(uint32_t network_long);
uint16_t packet_htons(uint16_t host_short);
uint32_t packet_htonl(uint32_t host_long);
int ntop(uint32_t src, char *dest);
int pton(char *src, void *dest);
void ip_hdr_ntoh(struct ip_hdr *ip_header);

#endif