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

        uint32_t host_ip = 0;
        uint32_t target_ip = 0;
        uint32_t ip_table[3] = {0};

        pton("192.168.0.155", &host_ip);

        pton("192.168.0.1", &target_ip);

        pton("192.168.0.1", &ip_table[0]);
        pton("192.168.0.2", &ip_table[1]);
        pton("192.168.0.8", &ip_table[2]);
        
        int arp_table_size = 3; 
        arp_hdr arp_table[arp_table_size];

        for(int i = 0; i < arp_table_size; i++){            

                send_arp_request(sock, host_ip, ip_table[i]);
                
                arp_recv_wait:
                
                recv_byte = recvfrom(sock, buffer, BUF_SIZ, 0, &saddr, &saddr_len);
                // 受信したパケットを ethdr にキャストして代入する
                // ethhdr については if_ether.h を参照
                ethernet_hdr *eth_h = (ethernet_hdr*)(buffer);
        
                struct ip_hdr *ip_h = (struct ip_hdr*)(buffer + sizeof(ethernet_hdr));

                // eth_hdr_dbg(eth_h, recv_byte);
                if(ntohs(eth_h->ethehertype) != ETH_T_ARP) goto arp_recv_wait;
                        
                arp_hdr *arp_h = (arp_hdr*)(buffer + sizeof(ethernet_hdr));
                        
                if(ntohs(arp_h->opcode) != ARP_OP_REPLY) goto arp_recv_wait;
                        
                arp_table[i] = *arp_h;
//                arp_dbg(&arp_table[i]);
        }

        char ip[IP_CHAR_LEN];

        printf("Network Address         MAC Address\n");
        for(int i = 0; i < arp_table_size; i++){
                ntop(ntohl(arp_table[i].sender_protocol_addr), ip);
                printf("%s             %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", ip,
                arp_table[i].sender_hw_addr[0],arp_table[i].sender_hw_addr[1],
                arp_table[i].sender_hw_addr[2],arp_table[i].sender_hw_addr[3],
                arp_table[i].sender_hw_addr[4],arp_table[i].sender_hw_addr[5]);
        }

}