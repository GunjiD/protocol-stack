
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

#include "ethernet.h"
#include "ip.h"
#include "inet.h"

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

while(1){
        recv_byte = recvfrom(sock, buffer, BUF_SIZ, 0, &saddr, &saddr_len);
        // 受信したパケットを ethdr にキャストして代入する
        // ethhdr については if_ether.h を参照
        struct ethernet_hdr *eth_h = (struct ethernet_hdr*)(buffer);        
        
//        eth_hdr_dbg(eth_h, recv_byte);
        
        struct ip_hdr *ip_h = (struct ip_hdr*)(buffer + sizeof(struct ethernet_hdr));

        ip_hdr_ntoh(ip_h);

        ip_hdr_dbg(ip_h, INTEGER);
        ip_hdr_dbg(ip_h, HEX);
}

return 0;
}

int create_socket(char *interface_name){

        // socket の file descriptor を開く
        int set_sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
        // インターフェースの設定を行う構造体
        struct ifreq if_set_pm;
        // 現在の状態を取得
        ioctl(sock, SIOCGIFFLAGS, &if_set_pm);

        //if_set_pm.ifr_flags |= IFF_PROMISC;
        if_set_pm.ifr_flags &= ~IFF_PROMISC;


        if(setsockopt(set_sock, SOL_SOCKET, SO_BINDTODEVICE, interface_name, IFNAMSIZ - 1) == -1){
                printf("not setting socket\n");
                exit(0);
        }
        return set_sock;
}