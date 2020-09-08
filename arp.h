#ifndef ARP_H
#define ARP_H

#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "ethernet.h"

typedef struct arp_hdr
{
        uint16_t hw_addr;
        uint16_t protocol_addr;
        uint8_t hw_addr_len;
        uint8_t protocol_addr_len;
        uint16_t opcode;
        char sender_hw_addr[ADDR_LEN];
        char sender_protocol_addr[ADDR_LEN];
        char target_hw_addr[ADDR_LEN];
        char target_protocol_addr[ADDR_LEN];
} Arp_h;

void send_arp_request();

#endif