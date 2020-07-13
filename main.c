#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>

#include "ethernet.h"

#define BUF_SIZ 65536

int create_socket();

int main(int argc, char *argv[]){

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
}
}