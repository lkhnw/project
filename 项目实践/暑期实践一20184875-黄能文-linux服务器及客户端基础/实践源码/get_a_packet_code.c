#include<stdlib.h>
#include<stdio.h>
#include <pcap.h>
int get_a_packet_code();
int main(){
//  printf("0ok");
  char error_content[PCAP_ERRBUF_SIZE];
  struct pcap_pkthdr protocol_header;
  pcap_t *pcap_handle;
//  printf("01ok");
  struct bpf_program  bpf_filter;
  char bpf_filter_string[] = "";
  const u_char *packet_content;
//  printf("1ok");
  bpf_u_int32 net_mask;
  bpf_u_int32 net_ip;
  char *net_interface;
  net_interface = pcap_lookupdev(error_content);
  pcap_lookupnet(net_interface,&net_ip,&net_mask,error_content);
  pcap_handle = pcap_open_live(net_interface,BUFSIZ,1,0,error_content);
//  printf("2ok");
  pcap_compile(pcap_handle,&bpf_filter,bpf_filter_string,0,net_ip);
  pcap_setfilter(pcap_handle,&bpf_filter);
  packet_content = pcap_next(pcap_handle,&protocol_header);
  printf("3ok");
  printf("Capture a packet from : %s\n",net_interface);
  printf("The packet length is :%d\n",protocol_header.len);
  pcap_close(pcap_handle);
}
