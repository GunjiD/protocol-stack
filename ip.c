#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "ip.h"
#include "inet.h"

void ip_hdr_dbg(struct ip_hdr *ip_header){

        ip_hdr_ntoh(ip_header);
    
        char ip_src[IP_STR_LEN];
        char ip_dest[IP_STR_LEN];
        ntop(ip_header->source_address, ip_src);
        ntop(ip_header->destination_address, ip_dest);

        printf("IP Header\n");
        printf("Version        : %d\n", ip_header->version);
        printf("IHL            : %d Bytes\n", (ip_header->ihl)*4);
        printf("Total Length   : %d Bytes\n", ntohs(ip_header->total_length));
        printf("Time To Live   : %d \n", ip_header->ttl);
        printf("Protocol       : %d \n", ip_header->protocol);
        printf("destination IP : %s\n", ip_dest);
        printf("source IP      : %s\n", ip_src);
        printf("==================================================\n");
}