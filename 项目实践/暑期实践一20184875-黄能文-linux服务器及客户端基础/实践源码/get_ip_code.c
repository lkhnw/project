#include "pcap.h"
struct ether_header{
  u_int8_t ether_dhost[6];
  u_int8_t ether_shost[8];
  u_int16_t ether_type;
};
typedef u_int32_t in_addr_t;
struct in_addr{
  in_addr_t s_addr;
};

struct ip_header{
  #ifdef WORDS_BIGENDIAN
  u_int8_t  ip_version:4,
            ip_header_length:4;
  #else
  u_int8_t  ip_header_length:4,
            ip_version:4;
  #endif
  u_int8_t  ip_tos;
  u_int16_t ip_length;
  u_int16_t ip_id;
  u_int16_t ip_off;
  u_int8_t  ip_ttl;
  u_int8_t  ip_protocol;
  u_int16_t ip_checksum;
  struct in_addr  ip_source_address;
  struct in_addr ip_destination_address;
};

void ip_protocol_packet_callback(u_char *argument,const struct pcap_pkthdr* packet_header,const u_char* packet_content){
  struct ip_header *ip_protocol;
  u_int header_length;
  u_int offset;
  u_char tos;
  u_int16_t checksum;
  ip_protocol = (struct ip_header *)(packet_content+14);
  checksum = ntohs(ip_protocol->ip_checksum);
  header_length = ip_protocol->ip_header_length*4;
  tos = ip_protocol->ip_tos;
  offset = ntohs(ip_protocol->ip_off);
  printf("------------ IP Protocol  (Network Layer------------\n");
  printf("IP Version:%d\n",ip_protocol->ip_version);
  printf("Header length:%d\n",header_length);
  printf("TOS:%d\n",tos);
  printf("Total length:%d\n",ntohs(ip_protocol->ip_length));
  printf("Identification:%d\n",ntohs(ip_protocol->ip_id));
  printf("Offset:%d\n",(offset&0x1fff)*8);
  printf("TTL:%d\n",ip_protocol->ip_ttl);
  printf("Protocol:%d\n",ip_protocol->ip_protocol);
  switch(ip_protocol->ip_protocol){
    case 6:  printf("The Transport Layer Protocol is TCP\n");break;
    case 17: printf("The Transport Layer Protocol is UDP\n");break;
    case 1: printf("The Transport Layer Protocol is ICMP\n");break;
    default: break;
  }
  printf("Header checksum:%d\n",checksum);
  printf("Source address:%s\n",inet_ntoa(ip_protocol->ip_source_address));
  printf("Destination address:%s\n",inet_ntoa(ip_protocol->ip_destination_address));
}

void ethernet_protocol_packet_callback(u_char *argument,const struct pcap_pkthdr* packet_header,const u_char* packet_content){
  u_short ethernet_type;
  struct ether_header *ethernet_protocol;
  u_char *mac_string;
  static int packet_number = 1;
    printf("**********************************************\n");
  printf("The %d IP packet is captured.\n",packet_number);
  printf("--------------Ethernet Protocol (Link Layer)------------------");
  ethernet_protocol = (struct ether_header *)packet_content;
  printf("Ethernet type is :\n");
  ethernet_type = ntohs(ethernet_protocol->ether_type);
  printf("%04x\n",ethernet_type);
  switch(ethernet_type){
    case 0x0800: printf("The network layer is IP protocol\n");break;
    case 0x0806: printf("The network layer is ARP protocol\n");break;
    case 0x8035: printf("The network layer is RARP protocol\n");break;
    default :break;
  }
  printf("Mac Source Address is : \n");
  mac_string = ethernet_protocol->ether_shost;
  printf("%02x:%02x:%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),
          *(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
  printf("Mac Destination Address is : \n");
  mac_string = ethernet_protocol->ether_dhost; 
  printf("%02x:%02x:%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),
          *(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
  switch(ethernet_type){
     case 0x0800:
     ip_protocol_packet_callback(argument,packet_header,packet_content);
     break;
     default :break;
  }
  printf("************************************************************\n");
  packet_number++;
}
void main(){
  printf("1");
  pcap_t* pcap_handle;
  char error_content[PCAP_ERRBUF_SIZE];
  char *net_interface;
  struct bpf_program bpf_filter;
  char bpf_filter_string[]="ip";
  bpf_u_int32 net_mask;
  bpf_u_int32 net_ip;
  printf("2");
  net_interface = pcap_lookupdev(error_content);
  pcap_lookupnet(net_interface,&net_ip,&net_mask,&error_content);
  pcap_handle = pcap_open_live(net_interface,BUFSIZ,1,0,error_content);
  pcap_compile(pcap_handle,&bpf_filter,bpf_filter_string,0,net_ip);
  printf("3");
  pcap_setfilter(pcap_handle,&bpf_filter);
  printf("5");
 // if(pcap_datalink(pcap_handle)!=DLT_EN10MB){return;}
  printf("6");
  pcap_loop(pcap_handle,-1,ethernet_protocol_packet_callback,NULL);
  pcap_close(pcap_handle);
  printf("4");
}
