#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "ip.h"
#include "inet.h"

void ip_hdr_dbg(struct ip_hdr *ip_header, int dump_form){

        char ip_src[IP_CHAR_LEN];
        char ip_dest[IP_CHAR_LEN];
        unsigned char *hdr = malloc(sizeof(unsigned char) * sizeof(*ip_header));

switch (dump_form){
        case INTEGER:
                ntop(ip_header->source_address, ip_src);
                ntop(ip_header->destination_address, ip_dest);
                printf("IP Header\n");
                printf("Version        : %d\n", ip_header->version);
                printf("IHL            : %d Bytes\n", (ip_header->ihl)*4);
                printf("Type_of_Service: %d \n", ip_header->type_of_service);
                printf("Total Length   : %d Bytes\n", ntohs(ip_header->total_length));                printf("Identification : %2x \n", ip_header->identification);
                printf("Flagment_Offset: %d \n", ip_header->fragment_offset);
                printf("Time To Live   : %d \n", ip_header->ttl);      
                printf("Protocol       : %d \n", ip_header->protocol);
                printf("Checksum       : %d \n", ip_header->hdr_checksum);
                printf("source IP      : %s\n", ip_src);
                printf("destination IP : %s\n", ip_dest);
                printf("==================================================\n");

        break;

        case HEX:
                memset(hdr,0, sizeof(unsigned char) * 20);
                // set binary of the IP header
                memcpy(hdr,ip_header, sizeof(*ip_header));
                for (int i = 0; i < sizeof(*ip_header); ++i) printf("%02X ", hdr[i]);
                printf("\n");
                printf("IP Header\n");
                printf("Version        : %x\n", ip_header->version);
                printf("IHL            : %x Bytes\n", ip_header->ihl);
                printf("Type_of_Service: %x \n", ip_header->type_of_service);
                printf("Total Length   : %2x Bytes\n", ip_header->total_length);
                printf("Identification : %2x \n", ip_header->identification);
                printf("Flagment_Offset: %2x \n", ip_header->fragment_offset);
                printf("Time To Live   : %x \n", ip_header->ttl);
                printf("Protocol       : %x \n", ip_header->protocol);
                printf("Checksum       : %2x \n", ip_header->hdr_checksum);
                printf("source IP      : %4x \n", ip_header->source_address);
                printf("destination IP : %4x \n", ip_header->destination_address);
                printf("__________________________________________________\n");

        break;
        }
}