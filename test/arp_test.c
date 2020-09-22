#include "arp.h"
#include "ethernet.h"
#include "ip.h"
#include "inet.h"
#include "raw_soc.h"

int sock;
// 受信したパケットのバイト数を格納
ssize_t recv_byte;

int main(int argc, char *argv[]){
        
        // プロトコルの情報が格納される
        struct sockaddr saddr;
        socklen_t saddr_len = sizeof(saddr);

        // パケットを受信する
        unsigned char *buffer = (unsigned char *) malloc(BUF_SIZ);
        memset(buffer,0, BUF_SIZ);

        sock = create_socket("enp9s0");

        uint32_t host_ip = 0xC0A8009B;  
        uint32_t target_ip = 0xC0A80001;

        send_arp_request(sock, host_ip, target_ip);

//        uint32_t ip_table[2] = {, };

while (1){
        recv_byte = recvfrom(sock, buffer, BUF_SIZ, 0, &saddr, &saddr_len);
        // 受信したパケットを ethdr にキャストして代入する
        // ethhdr については if_ether.h を参照
        ethernet_hdr *eth_h = (ethernet_hdr*)(buffer);        
        
        struct ip_hdr *ip_h = (struct ip_hdr*)(buffer + sizeof(ethernet_hdr));

//        eth_hdr_dbg(eth_h, recv_byte);

        arp_hdr arp_table[2];

if(ntohs(eth_h->ethehertype) == ETH_T_ARP){

        arp_hdr *arp_h = (arp_hdr*)(buffer + sizeof(ethernet_hdr));

        arp_table[0] = *arp_h;

//        arp_dbg(arp_h);
        arp_dbg(&arp_table[0]);

/*
//        ip_hdr_dbg(ip_h, HEX);
        ip_hdr_ntoh(ip_h);
        ip_hdr_dbg(ip_h, INTEGER);
*/

}

}
}