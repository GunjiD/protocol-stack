#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
//#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>

#include "ethernet.h"

#define BUF_SIZ 65536

char *dest_addr(Eth_h *eth_hdr){
        char *str;
        sprintf(str, "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", eth_hdr->dest[0],eth_hdr->dest[1],eth_hdr->dest[2],eth_hdr->dest[3],eth_hdr->dest[4],eth_hdr->dest[5]);
        return str;
}

char *src_addr(Eth_h *eth_hdr){
        char *str;
        sprintf(str, "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", eth_hdr->src[0],eth_hdr->src[1],eth_hdr->src[2],eth_hdr->src[3],eth_hdr->src[4],eth_hdr->src[5]);
        return str;
}

void eth_hdr_dbg(struct ethernet_hdr *eth_header, ssize_t recv_byte){

                // Ethernet Header の解析
        printf("Ethernet Header\n");
        // 宛先アドレスの MAC アドレスを表示
        printf("destination address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
                        eth_header->dest[0],eth_header->dest[1],eth_header->dest[2],eth_header->dest[3],eth_header->dest[4],eth_header->dest[5]);
        printf("source address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
                        eth_header->src[0],eth_header->src[1],eth_header->src[2],eth_header->src[3],eth_header->src[4],eth_header->src[5]);
        printf("Packet Type ID : %d\n", eth_header->ethehertype);
        printf("packet %lu bytes\n", byte);
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
}