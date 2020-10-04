#include "inet.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ip.h"

int host_byte_order(void){
    
    int x=0x00000001;
    
    if (*(char*)&x) {
            return __LITTLE_ENDIAN;
        }else{
            return __BIG_ENDIAN;
        }
}
//  this implementation referrd to byteswap.h
uint16_t byte_swap16(uint16_t x){
    return (x & 0x00ff) << 8 | (x & 0xff00) >> 8;
}

uint32_t byte_swap32(uint32_t x){
    return (x & 0x000000ff) << 24 | (x & 0x0000ff00) << 8 | (x & 0x00ff0000) >> 8 | (x & 0xff000000) >> 24;
}

uint16_t ntohs(uint16_t network_short){

    uint16_t tmp = 0;
    tmp = (network_short >> 8) | (network_short << 8);

    return tmp;
}

uint32_t ntohl(uint32_t network_long){

    if(host_byte_order() == LITTLE_ENDIAN){
        return byte_swap32(network_long);
    }else{
        return network_long;
    }
}

uint16_t htons(uint16_t host_short){
    uint16_t tmp = 0;
    tmp = (host_short << 0) & 0xff00;
    tmp = tmp >> 8;
    tmp |= (host_short << 8) & 0xff00;

    return tmp;
}
uint32_t htonl(uint32_t host_long){

    uint32_t tmp = 0;
    for(int i = 0; i < 4; i++){
    tmp |= (host_long << i * 8) &0xff000000;
    if(i == 3) break;
    tmp = tmp >> 8;
    }

    return tmp;    
}

void ntop(u_int32_t src, char *dest){
    u_char addr[16];
    sprintf(addr,"%u.%u.%u.%u",(src >>  24) & 0xFF,(src >>  16) & 0xFF,(src >>  8) & 0xFF,(src >>  0) & 0xFF);
    strcpy(dest, addr);    
}

void ip_hdr_ntoh(struct ip_hdr *ip_header){
        uint8_t tmp_ip_ver = ip_header->version;
        ip_header->version = ip_header->ihl;
        ip_header->ihl = tmp_ip_ver;
        ip_header->total_length = ntohs(ip_header->total_length);
        ip_header->fragment_offset = ntohl(ip_header->fragment_offset);
        ip_header->hdr_checksum = ntohs(ip_header->hdr_checksum);
        ip_header->source_address = ntohl(ip_header->source_address);
        ip_header->destination_address = ntohl(ip_header->destination_address);
}