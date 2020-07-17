#ifndef ETHERNET_H
#define ETHERNET_H

#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>



typedef struct ip_hdr
{
    version 4bit
    ihl 4bit
    type of service 8bit
    total length 16bit
    identification 16bit
    flags 3bit
    fragment offset 13bit
    time to live 8bit
    protocol 8bit
    header checksum 16bit
    source address 32bit
    destination address 32bit
    options 
    padding
} Ip_h;

#endif