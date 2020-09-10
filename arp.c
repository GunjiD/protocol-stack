#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "arp.h"
#include "ethernet.h"
#include "inet.h"

void send_arp_request(int sd){

     ethernet_hdr eth_h;
   // must be entered <protocol type, sender protocol address, sender hardware address> in the arp_hdr.
    arp_hdr arp_h;

    unsigned char host_mac[6] = {0xA8, 0xA1, 0x59, 0x2D, 0x0D, 0x17};
    unsigned char target_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    strcpy(eth_h.dest, broadcast);
    strcpy(eth_h.src, host_mac);
    eth_h.ethehertype = 0x0806; // set arp

    arp_h.hw_addr_space = 1;
    arp_h.protocol_addr_space = 0x0800;
    arp_h.hw_addr_len = 6;
    arp_h.protocol_addr_len = 4;    
    arp_h.opcode = 1;
    strcpy(arp_h.sender_hw_addr, host_mac);
    arp_h.sender_protocol_addr = 0xC0A8009C; //192.168.0.156
    strcpy(arp_h.target_hw_addr, target_mac);
    arp_h.target_protocol_addr = 0xC0A80001; //192.168.0.1

    unsigned char *buff = (unsigned char *) malloc(65536);
    memset(buff, 0, 65536);

    printf("%ld\n", sizeof( ethernet_hdr));
    printf("%ld\n", sizeof(arp_hdr));

//    for(int i = 0; i < 6; i++) printf("%02x ",arp_h.sender_hw_addr[i]);

//    printf("%s\n", arp_h->sender_hw_addr);

//    send(sd,);
}