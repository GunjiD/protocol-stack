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

    unsigned char *buff = (unsigned char *) malloc(65536);
    memset(buff, 0, 65536);

    unsigned char host_mac[6]   = {0xA8, 0xA1, 0x59, 0x2D, 0x0D, 0x17};
    unsigned char target_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char broadcast[6]  = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    memcpy(eth_h.dest, broadcast, 6);
    memcpy(eth_h.src, host_mac, 6);
    eth_h.ethehertype = htons((uint16_t)0x0806); // set arp

    arp_h.hw_addr_space = htons((uint16_t)0x0001);
    arp_h.protocol_addr_space = htons((uint16_t)0x0800);
    arp_h.hw_addr_len = 6;
    arp_h.protocol_addr_len = 4;    
    arp_h.opcode = htons((uint16_t)0x0001);
    memcpy(arp_h.sender_hw_addr, host_mac, 6);
    arp_h.sender_protocol_addr = htonl((uint32_t)0xC0A8009B); //192.168.0.155
    memcpy(arp_h.target_hw_addr, target_mac, 6);
    arp_h.target_protocol_addr = htonl((uint32_t)0xC0A800FF); //192.168.0.1


//    printf("struct ethernet_hdr size %ld Byte\n", sizeof(ethernet_hdr));
//    printf("struct arp_hdr %ld Byte\n", sizeof(arp_hdr));

    memcpy(buff, &eth_h, sizeof(ethernet_hdr));
    memcpy(buff + sizeof(ethernet_hdr), &arp_h, sizeof(arp_hdr));
//    memcpy(buff + sizeof(ethernet_hdr), &arp_h, sizeof(arp_hdr));

//    for(int i = 0; i < 42; i++) printf("%02x ",buff[i]);

    ssize_t send_byte = send(sd, buff, 44, 0);

    if(send_byte == -1){
        perror("send");
    }

    printf("transmmit arp %ld Byte\n",send_byte);
}