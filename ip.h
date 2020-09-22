#ifndef IP_H
#define IP_H

#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "ethernet.h"

#define IP_CHAR_LEN 16
#define HEX 0
#define INTEGER 1
#define BUF_SIZ 65535


typedef struct ip_hdr
{
    uint8_t version:4;
    uint8_t ihl:4;
    uint8_t type_of_service;
    uint16_t total_length;
    uint16_t identification;
    uint16_t fragment_offset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t hdr_checksum;
    uint32_t source_address;
    uint32_t destination_address;
//    options 
//    padding
} Ip_h;

void ip_hdr_dbg(struct ip_hdr *ip_header, int dump_form);

#endif