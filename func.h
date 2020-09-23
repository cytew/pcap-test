#pragma once

#include <stdio.h>


void ether_mac_address(const u_char* packet);
void ip_address(const u_char* packet);
void tcp_ports(const u_char* packet);
void payload_hex_value(const u_char* packet,int len);
