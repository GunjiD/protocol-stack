#include "inet.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t ntohs(uint16_t network_short){

    uint16_t tmp = 0;
    tmp = (network_short >> 0) & 0xff;
    tmp = tmp << 8;
    tmp |= (network_short >> 8) & 0xff;

    return tmp;
}

uint32_t ntohl(uint32_t network_long){

    uint32_t tmp = 0;
    for(int i = 0; i < 4; i++){
    tmp |= (network_long >> i * 8) &0xff;
    if(i == 3) break;
    tmp = tmp << 8;
    }

    return tmp;    
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