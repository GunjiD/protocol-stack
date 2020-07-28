#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "ip.h"

void ip_ntop(u_int32_t src, char *dest){
    u_char addr[16];
    sprintf(addr,"%u.%u.%u.%u",(src >>  0) & 0xFF,(src >>  8) & 0xFF,(src >>  16) & 0xFF,(src >>  24) & 0xFF);
    strcpy(dest, addr);    
}