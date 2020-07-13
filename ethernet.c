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