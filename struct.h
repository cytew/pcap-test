#define LIBNET_ETH_H            0x0e    /**< Ethernet header:     14 bytes */
#define LIBNET_IPV4_H           0x14    /**< IPv4 header:         20 bytes */
#define LIBNET_TCP_H            0x14    /**< TCP header:          20 bytes */
#define ETHER_ADDR_LEN 6


struct libnet_ethernet_hdr
{
    u_int8_t  ether_dhost[ETHER_ADDR_LEN];/* destination ethernet address */
    u_int8_t  ether_shost[ETHER_ADDR_LEN];/* source ethernet address */
    u_int16_t ether_type;                 /* protocol */
};



struct libnet_ipv4_hdr
{
    struct in_addr ip_src;
    struct in_addr ip_dst; /* source and dest address */
};



struct libnet_tcp_hdr
{
    u_int16_t th_sport;       /* source port */
    u_int16_t th_dport;       /* destination port */
};