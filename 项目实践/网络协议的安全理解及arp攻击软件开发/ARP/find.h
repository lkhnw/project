#pragma once
#include "pch.h"
#include "pcap.h"
#include <windows.h>
#pragma comment(lib,"wpcap.lib")
#pragma comment(lib,"Packet.lib")
#pragma comment(lib,"ws2_32.lib")
class find
{
public:
	pcap_if_t* devs;
	pcap_t* dev;
	char* get_devs();
	void set_dev();
	char* find_packet();

};

