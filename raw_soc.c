#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <net/if.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <errno.h>

#include "ethernet.h"
#include "ip.h"
#include "inet.h"
#include "arp.h"

int create_socket(char *interface_name){

        int soc;
        // インターフェースの設定を行う構造体
        struct ifreq if_req;
        struct sockaddr_ll sa;
        
        if((soc = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1){
                perror("raw_socket");
                exit(0);
        }

        // set the interface name to ifreq using strncpy
        strncpy(if_req.ifr_name, interface_name, IFNAMSIZ);
        if(ioctl(soc, SIOCGIFINDEX, &if_req) == -1){
                fprintf(stderr, "SIOCGIFINDEX errno %d %s\n", errno, strerror(errno));
                exit(0);
        }

        // bind to interface
        sa.sll_family = PF_PACKET;
        sa.sll_protocol = htons(ETH_P_ALL);
        sa.sll_ifindex = if_req.ifr_ifindex;
        if(bind(soc,(struct sockaddr *) &sa, sizeof(sa)) == -1){
                perror("bind");
                exit(0);
        }
        
        //if_req.ifr_flags |= IFF_PROMISC;
        if_req.ifr_flags &= ~IFF_PROMISC;

        //set flag of interface to UP
        if_req.ifr_flags = if_req.ifr_flags | IFF_UP;

        //set flag of interface
        if(ioctl(soc, SIOCGIFFLAGS, &if_req) == -1){
                fprintf(stderr, "ioctl: errno %d %s\n", errno, strerror(errno));
                exit(0);
        }
/*
           setsockopt(soc, IPPROTO_IP, IP_HDRINCL, val, sizeof(one))
        if(setsockopt(soc, SOL_SOCKET, SO_BINDTODEVICE, interface_name, IFNAMSIZ - 1) == -1){
                printf("not setting socket\n");
                exit(0);
        }
*/
        return soc;
}