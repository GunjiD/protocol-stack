#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
//#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>

#include "ethernet.h"

#define BUF_SIZ 65536

struct ethernet_hdr
{
        unsigned char dest[ADDR_LEN];
        unsigned char src[ADDR_LEN];
        unsigned short ethehertype;
};

char *dest_addr(Eth_h *eth_hdr){
        char *str;
        sprintf(str, "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", eth_hdr->dest[0],eth_hdr->dest[1],eth_hdr->dest[2],eth_hdr->dest[3],eth_hdr->dest[4],eth_hdr->dest[5]);
        return str;
}

char *src_addr(Eth_h *eth_hdr){
        char *str;
        sprintf(str, "%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", eth_hdr->src[0],eth_hdr->src[1],eth_hdr->src[2],eth_hdr->src[3],eth_hdr->src[4],eth_hdr->src[5]);
        return str;
}


int create_socket();

// socket は権限が必要なので注意

//man socket(2) を参照
//第三引数については man packet(7) を参照。これを設定しているとすべてのパケットを受信する。
// int socket()

int main(int argc, char *argv[]){
/*
 * ディスクリプタを返す //// man socket(7)より
 *
 * */

create_socket();

return 0;
}

int create_socket(){
        // socket の file descriptor を開く
        int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
        // インターフェースの設定を行う構造体
        struct ifreq if_set_pm;
        // プロトコルの情報が格納される
        struct sockaddr saddr;
        socklen_t saddr_len = sizeof(saddr);
        // 受信したパケットのバイト数を格納
        ssize_t recv_byte;
        // パケットを受信する
        unsigned char *buffer = (unsigned char *) malloc(BUF_SIZ);
        memset(buffer,0, BUF_SIZ);

        // インターフェースの指定
        strncpy(if_set_pm.ifr_name, "eth0", IFNAMSIZ - 1);
        // 現在の状態を取得
        ioctl(sock, SIOCGIFFLAGS, &if_set_pm);
        // or でビットを立てる
        if_set_pm.ifr_flags |= IFF_PROMISC;
        // プロミスキャスモードの反映
        ioctl(sock, SIOCSIFFLAGS, &if_set_pm);
        // socket の設定を行う。 man getsockopt(2)
        // インターフェースの名前はOS毎に違うので要注意
        if(setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, "enp9s0", IFNAMSIZ - 1) == -1){
                // エラー時には -1
                printf("not setting socket\n");
                return 1;
        }

while(1){
        recv_byte = recvfrom(sock, buffer, BUF_SIZ, 0, &saddr, &saddr_len);
        // 受信したパケットを ethdr にキャストして代入する
        // ethhdr については if_ether.h を参照
        struct ethernet_hdr *eth_h = (struct ethernet_hdr*)(buffer);
        
        printf("Ethernet Header\n");
        // 宛先アドレスの MAC アドレスを表示
        printf("destination address : %s\n", dest_addr(eth_h));
        printf("source address      : %s\n", src_addr(eth_h));
        printf("Packet Type ID : %d\n", eth_h->ethehertype);
        printf("packet %lu bytes\n", recv_byte);
        printf("==================================================\n");

        /*
        // ethernet header の分を移動させることで IP header を抜き出す
        struct iphdr *ip_h = (struct iphdr*)(buffer + sizeof(struct ethhdr));

        char src_addr[INET_ADDRSTRLEN];
        char dst_addr[INET_ADDRSTRLEN];
        //送信元IPアドレス
        //宛先IPアドレス
        inet_ntop(AF_INET, &ip_h->saddr, src_addr, sizeof(src_addr));
        inet_ntop(AF_INET, &ip_h->daddr, dst_addr, sizeof(dst_addr));

        printf("IP Header\n");
        printf("Version        : %d\n", (unsigned int)ip_h->version);
        printf("IHL            : %d Bytes\n", (unsigned int)(ip_h->ihl)*4);
        printf("Total Length   : %d Bytes\n", ntohs(ip_h->tot_len));
        printf("Time To Live   : %d \n", (unsigned int)ip_h->ttl);
        printf("Protocol       : %d \n", (unsigned int)ip_h->protocol);
        printf("source IP      : %s\n", src_addr);
        printf("destination IP : %s\n", dst_addr);
        printf("==================================================\n");
        //for(int i=0; i < sizeof(buf); i++) printf("%02X", buf[i]);
        //printf("interface = %s \n", if_set_pm.ifr_name);

        __u8 iphdr_len = ip_h->ihl*4;

        struct tcphdr *udp_h = (struct tcphdr*)(buffer+ iphdr_len + sizeof(struct ethhdr));

        printf("Source Port %d\n", udp_h->source);

        */
}
}