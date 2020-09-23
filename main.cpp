#include <pcap.h>
#include <stdio.h>
#include "func.h"

void usage() {
    printf("syntax: pcap-test <interface>\n");
    printf("sample: pcap-test wlan0\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        usage();
        return -1;
    }

    char* dev = argv[1];
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        fprintf(stderr, "pcap_open_live(%s) return null - %s\n", dev, errbuf);
        return -1;
    }
    int cnt =0;

    while (true) {
        struct pcap_pkthdr* header;
        const u_char* packet;
        int res = pcap_next_ex(handle, &header, &packet); //get the latest packet
        if (res == 0) continue;
        if (res == -1 || res == -2) {
            printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(handle));
            break;
        }

        cnt+=1;
        int payload_offset=header->caplen;

        if(packet[12]==0x08 && packet[13]==0x00 && packet[23]==0x06){
        printf("-------------------------------------------\n");
        printf("NUM.%d %u bytes captured\n\n",cnt, header->caplen); //capture len
        ether_mac_address(packet);
        ip_address(packet);
        tcp_ports(packet);
	    payload_hex_value(packet,payload_offset);
        printf("-------------------------------------------\n");
        }
        else
        printf("NUM.%d This is not a TCP Packet\n",cnt);
    }


    pcap_close(handle);
}
