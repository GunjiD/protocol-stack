#ifndef ARP_H
#define ARP_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct arp_hdr
{
        uint16_t hw_addr;
        uint16_t protocol_addr;
        uint8_t hw_addr_len;
        uint8_t protocol_addr_len;
        uint16_t opcode;
        unsigned char sender_hw_addr[ADDR_LEN];
        uint32_t sender_protocol_addr;
        unsigned char target_hw_addr[ADDR_LEN];
        uint32_t target_protocol_addr;
} Arp_h;

void send_arp_request();

#endif