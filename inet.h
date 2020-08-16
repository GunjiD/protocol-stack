#ifndef BYTE_ORDER_H
#define BYTE_ORDER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ip.h"

uint16_t packet_ntohs(uint16_t network_short);
uint32_t packet_ntohl(uint32_t network_long);
uint16_t packet_htons(uint16_t host_short);
uint32_t packet_htonl(uint32_t host_long);
void ntop(uint32_t src, char *dest);
void ip_hdr_ntoh(struct ip_hdr *ip_header);

#endif