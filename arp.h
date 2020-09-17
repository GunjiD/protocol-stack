#ifndef ARP_H
#define ARP_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ethernet.h"
#include "ip.h"

typedef struct ARP_HEADER
{
        uint16_t hw_addr_space;
        uint16_t protocol_addr_space;
        uint8_t hw_addr_len;
        uint8_t protocol_addr_len;
        uint16_t opcode;
        unsigned char sender_hw_addr[MAC_LEN];
        uint32_t sender_protocol_addr;
        unsigned char target_hw_addr[MAC_LEN];
        uint32_t target_protocol_addr;
} __attribute__((packed)) arp_hdr;

void send_arp_request(int sd);
void arp_dbg(arp_hdr *arp_h);

#endif