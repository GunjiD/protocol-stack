
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

#define BUF_SIZ 65536

int sock;
// 受信したパケットのバイト数を格納
ssize_t recv_byte;

int create_socket(char *interface_name);

int main(int argc, char *argv[]){
        
        // プロトコルの情報が格納される
        struct sockaddr saddr;
        socklen_t saddr_len = sizeof(saddr);

        // パケットを受信する
        unsigned char *buffer = (unsigned char *) malloc(BUF_SIZ);
        memset(buffer,0, BUF_SIZ);

        sock = create_socket("enp9s0");

//        send_arp_request(sock);

        uint16_t a = 0x1122;

        printf("%4x\n",a);
        printf("%4x\n",ntohs(a));
        uint32_t b = 0x11223344;
        printf("%8x\n",b);
        printf("%8x\n",ntohl(b));

        return 0;

while(1){

        recv_byte = recvfrom(sock, buffer, BUF_SIZ, 0, &saddr, &saddr_len);
        // 受信したパケットを ethdr にキャストして代入する
        // ethhdr については if_ether.h を参照
        ethernet_hdr *eth_h = (ethernet_hdr*)(buffer);        
        
        struct ip_hdr *ip_h = (struct ip_hdr*)(buffer + sizeof(ethernet_hdr));

//        eth_hdr_dbg(eth_h, recv_byte);

if(ntohs(eth_h->ethehertype) == 0x0806){
        arp_hdr *arp_h = (arp_hdr*)(buffer + sizeof(ethernet_hdr));
        arp_dbg(arp_h);
/*
//        ip_hdr_dbg(ip_h, HEX);
        ip_hdr_ntoh(ip_h);
        ip_hdr_dbg(ip_h, INTEGER);
*/

}

}

return 0;
}

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