#ifndef ETHERNET_H
#define ETHERNET_H

#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>



typedef struct ip_hdr
{
    uint8_t version:4;
    uint8_t ihl:4;
    uint8_t type_of_service;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags:3;
    uint16_t fragment_offset:13;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t hdr_checksum;
    uint32_t source_address;
    uint32_t destination_address;
//    options 
//    padding
} Ip_h;

#endif