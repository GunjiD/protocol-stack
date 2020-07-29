
#include <string.h>
#include <arpa/inet.h>
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

#define BUF_SIZ 65536

int sock;
// 受信したパケットのバイト数を格納
ssize_t recv_byte;

int create_socket(int set_sock, char *interface, char *interface_name);

int main(int argc, char *argv[]){
        
        // プロトコルの情報が格納される
        struct sockaddr saddr;
        socklen_t saddr_len = sizeof(saddr);


        // パケットを受信する
        unsigned char *buffer = (unsigned char *) malloc(BUF_SIZ);
        memset(buffer,0, BUF_SIZ);

        sock = create_socket(sock, "eth0", "enp9s0");

while(1){
        recv_byte = recvfrom(sock, buffer, BUF_SIZ, 0, &saddr, &saddr_len);
        // 受信したパケットを ethdr にキャストして代入する
        // ethhdr については if_ether.h を参照
        struct ethernet_hdr *eth_h = (struct ethernet_hdr*)(buffer);        
        
        // Ethernet Header の解析
        printf("Ethernet Header\n");
        // 宛先アドレスの MAC アドレスを表示
        printf("destination address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
                        eth_h->dest[0],eth_h->dest[1],eth_h->dest[2],eth_h->dest[3],eth_h->dest[4],eth_h->dest[5]);
        printf("source address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
                        eth_h->src[0],eth_h->src[1],eth_h->src[2],eth_h->src[3],eth_h->src[4],eth_h->src[5]);
        printf("Packet Type ID : %d\n", eth_h->ethehertype);
        printf("packet %lu bytes\n", recv_byte);
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        
        // IP Header の解析
        struct ip_hdr *ip_h = (struct ip_hdr*)(buffer + sizeof(struct ethernet_hdr));

        char ip_src[IP_STR_LEN];
        char ip_dest[IP_STR_LEN];
        ip_ntop(ip_h->source_address, ip_src);
        ip_ntop(ip_h->destination_address, ip_dest);
        
        printf("IP Header\n");
        printf("Version        : %d\n", ip_h->version);
        printf("IHL            : %d Bytes\n", (ip_h->ihl)*4);
        printf("Total Length   : %d Bytes\n", ntohs(ip_h->total_length));
        printf("Time To Live   : %d \n", ip_h->ttl);
        printf("Protocol       : %d \n", ip_h->protocol);
        printf("destination IP : %s\n", ip_dest);
        printf("source IP      : %s\n", ip_src);
        printf("==================================================\n");
}

return 0;
}

int create_socket(int set_sock, char *interface, char *interface_name){

        // socket の file descriptor を開く
        set_sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
        // インターフェースの設定を行う構造体
        struct ifreq if_set_pm;
        // インターフェースの指定
        strncpy(if_set_pm.ifr_name, interface, IFNAMSIZ - 1);
        // 現在の状態を取得
        ioctl(sock, SIOCGIFFLAGS, &if_set_pm);
        // or でビットを立てる
        if_set_pm.ifr_flags |= IFF_PROMISC;
        
        if(setsockopt(set_sock, SOL_SOCKET, SO_BINDTODEVICE, interface_name, IFNAMSIZ - 1) == -1){
                // エラー時には -1
                printf("not setting socket\n");
                return 1;
        }
        return set_sock;
}