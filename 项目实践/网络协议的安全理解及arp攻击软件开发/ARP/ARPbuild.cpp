#include "pch.h"
#include "ARPbuild.h"
#include "pcap.h"
#include <windows.h>
#pragma comment(lib,"wpcap.lib")
#pragma comment(lib,"Packet.lib")
#pragma comment(lib,"ws2_32.lib")

void ARPbuild::sendarp(char* srcmac, char* srcip, char* desmac, char* desip, int num, int time)
{
	init();
	set_srcmac(srcmac);
	set_srcip(srcip);
	set_desmac(desmac);
	set_desip(desip);
    set_else(num,time);
}

void ARPbuild::init()
{
    //作为一个arp包有些是固定的。
    //以太网帧的服务类型，
    packet[12] = 0x08;//12、13位为帧类型
    packet[13] = 0x06;
    //ARP首部
    packet[14] = 0x00;//14、15位为硬件类型
    packet[15] = 0x01;
    packet[16] = 0x08;//16、17位为协议类型
    packet[17] = 0x00;
    packet[18] = 0x06;//硬件地址长度
    packet[19] = 0x04;//协议地址长度
    packet[20] = 0x00;//op
    packet[21] = 0x01;//只做请求
    //填充42到59字节
    for (int i = 0; i < 18; i++)
    {
       packet[42 + i] = 0;
    }
}

void ARPbuild::set_srcmac(char* srcmac)
{
    //6-12,22-28
    int k = 0, temp[3];
    for (int i = 0; i < 18; i = i + 3) {
        temp[0] = (int)srcmac[i];
        temp[1] = (int)srcmac[i + 1];
        if (temp[0] > 96)         //当输入mac为小写字母时字符转换为16进制
            temp[0] = temp[0] - 87;
        else if (temp[0] > 64)
            temp[0] = temp[0] - 55;//当输入mac为大写字母时字符转换为16进制
        else
            temp[0] = temp[0] - 48;//当输入mac为数字时字符转换为16进制
        if (temp[1] > 96)
            temp[1] = temp[1] - 87;
        else if (temp[1] > 64)
            temp[1] = temp[1] - 55;
        else
            temp[1] = temp[1] - 48;
        packet[6+k] = packet[22 + k] = temp[0] * 16 + temp[1];
        k++;
    }
}

void ARPbuild::set_srcip(char* srcip)
{
    //源ip，28-32
    int k = 0,temp[3],j;
    temp[2] = 0;  //指向每个字节初始位置
    for (int i = 0; i < 4; i++)
    {
      temp[0] = 0;
      temp[1] = 0;
      for (j = 0; j < 4; j++)
      {
          if (srcip[j + temp[2]] >= '0' && srcip[j + temp[2]] <= '9')
          {
              //有点东西，temp 0，1用来存数，temp 2用来记位置。
              temp[0] = (int)srcip[j + temp[2]] - 48;
              temp[1] = temp[1] * 10 + temp[0];
          }
         else
         {
           //当遇到点时j自加1目的是让temp[2]+j指向下一字节的第一位
            j++;
          break;
         }
      }
      packet[28 + k] = temp[1];
      k++;
      temp[2] += j;
    }
}

void ARPbuild::set_desmac(char* desmac)
{
	//0-6，32-38
    int k = 0,temp[3];
    for (int i = 0; i < 18; i = i + 3){
          temp[0] = (int)desmac[i];
          temp[1] = (int)desmac[i + 1];
          if (temp[0] > 96)         //当输入mac为小写字母时字符转换为16进制
               temp[0] = temp[0] - 87;
          else if (temp[0] > 64)
               temp[0] = temp[0] - 55;//当输入mac为大写字母时字符转换为16进制
          else
                temp[0] = temp[0] - 48;//当输入mac为数字时字符转换为16进制
          if (temp[1] > 96)
               temp[1] = temp[1] - 87;
          else if (temp[1] > 64)
               temp[1] = temp[1] - 55;
          else
               temp[1] = temp[1] - 48;
          packet[k] = packet[32 + k] = temp[0] * 16 + temp[1];
          k++;
          }
}

void ARPbuild::set_desip(char* desip)
{
    //目的ip，38-42
    int k = 0, temp[3], j;
    temp[2] = 0;  //指向每个字节初始位置
    for (int i = 0; i < 4; i++)
    {
        temp[0] = 0;
        temp[1] = 0;
        for (j = 0; j < 4; j++)
        {
            if (desip[j + temp[2]] >= '0' && desip[j + temp[2]] <= '9')
            {
                //有点东西，temp 0，1用来存数，temp 2用来记位置。
                temp[0] = (int)desip[j + temp[2]] - 48;
                temp[1] = temp[1] * 10 + temp[0];
            }
            else
            {
                //当遇到点时j自加1目的是让temp[2]+j指向下一字节的第一位
                j++;
                break;
            }
        }
        packet[38 + k] = temp[1];
        k++;
        temp[2] += j;
    }
}

void ARPbuild::set_else(int num, int time)
{
    //设置网卡并发送
    pcap_if_t* alldevs;
    pcap_if_t* d;
    pcap_t* adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_findalldevs(&alldevs,errbuf);
    int numofdevs = 0;
    for (d = alldevs; d; d = d->next){
        numofdevs++;
    }
    if (numofdevs == 0) {
        printf("error");
    }
    //设置循环次数和间隔
    for (int n = 0; n < num; n++) {
        int i = 0;
        for (d = alldevs; i < numofdevs; d = d->next, i++) {
            adhandle = pcap_open_live(d->name, //设备名 
                65536, // 最大捕捉字节数 
                1, // 混杂模式 
                1000, // 读入超时 
                errbuf // 错误缓冲 
            );
            pcap_sendpacket(adhandle, packet, 64);
            pcap_close(adhandle);
        }
        Sleep(10*time);
    }
    pcap_freealldevs(alldevs);
}
