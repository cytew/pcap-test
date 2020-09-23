#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_ntop
#include "func.h"
#include "struct.h"

#define ETHER_ADDR_LEN 6


void ether_mac_address(const u_char* packet){
    struct libnet_ethernet_hdr *ep;
    ep= (struct libnet_ethernet_hdr*)packet;

    printf("1. Ethernet Header src mac / dst mac\n");
	printf("   SOURCE MAC address: %02X:%02X:%02X:%02X:%02X:%02X \n",ep->ether_shost[0], ep->ether_shost[1], ep->ether_shost[2],
			ep->ether_shost[3], ep->ether_shost[4], ep->ether_shost[5]);
	printf("   DESTINATION MAC address: %02X:%02X:%02X:%02X:%02X:%02X \n\n", ep->ether_dhost[0], ep->ether_dhost[1],ep->ether_dhost[2],
			ep->ether_dhost[3], ep->ether_dhost[4], ep->ether_dhost[5]);

}

void ip_address(const u_char* packet){
    char ip_src[16];
	char ip_dst[16];
	struct libnet_ipv4_hdr *source;

	source = (struct libnet_ipv4_hdr*)(packet+26);

	inet_ntop(AF_INET, &source->ip_src, ip_src, sizeof(ip_src)); //network data to char
	inet_ntop(AF_INET, &source->ip_dst, ip_dst, sizeof(ip_dst));

	printf("2. IP Header src ip / dst ip\n");
	printf("   SOURCE IP address: %s \n", ip_src);
	printf("   DESTINATION IP address: %s \n\n", ip_dst);


}

void tcp_ports(const u_char* packet){
	struct libnet_tcp_hdr *tp;
    tp= (struct libnet_tcp_hdr*)(packet+34);

	printf("3. TCP Header src port / dst port\n");
	printf("   SOURCE PORT: %d \n", ntohs(tp->th_sport));
	printf("   DESTINATION PORT : %d \n\n", ntohs(tp->th_dport));
	


}


void payload_hex_value(const u_char* packet, int len){
	int payload_offset=66;
	
	printf("4. Payload hexadecimal value\n");
	
	if(len-payload_offset<=0)
	{
		printf("\n   There is no data\n");
	} 
	else if(len-payload_offset>16){
	for(int i=0; i<16; i++){
		
		printf("%02X ", packet[i+payload_offset]);
	
	}
	}
	else{
	for(int i=0; i<len-payload_offset; i++){
		
		printf("%02X ", packet[i+payload_offset]);
	
	}
	}
	printf("\n\n");
	
}
