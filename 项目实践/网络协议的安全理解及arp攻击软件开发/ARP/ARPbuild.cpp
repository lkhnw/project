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
    //��Ϊһ��arp����Щ�ǹ̶��ġ�
    //��̫��֡�ķ������ͣ�
    packet[12] = 0x08;//12��13λΪ֡����
    packet[13] = 0x06;
    //ARP�ײ�
    packet[14] = 0x00;//14��15λΪӲ������
    packet[15] = 0x01;
    packet[16] = 0x08;//16��17λΪЭ������
    packet[17] = 0x00;
    packet[18] = 0x06;//Ӳ����ַ����
    packet[19] = 0x04;//Э���ַ����
    packet[20] = 0x00;//op
    packet[21] = 0x01;//ֻ������
    //���42��59�ֽ�
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
        if (temp[0] > 96)         //������macΪСд��ĸʱ�ַ�ת��Ϊ16����
            temp[0] = temp[0] - 87;
        else if (temp[0] > 64)
            temp[0] = temp[0] - 55;//������macΪ��д��ĸʱ�ַ�ת��Ϊ16����
        else
            temp[0] = temp[0] - 48;//������macΪ����ʱ�ַ�ת��Ϊ16����
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
    //Դip��28-32
    int k = 0,temp[3],j;
    temp[2] = 0;  //ָ��ÿ���ֽڳ�ʼλ��
    for (int i = 0; i < 4; i++)
    {
      temp[0] = 0;
      temp[1] = 0;
      for (j = 0; j < 4; j++)
      {
          if (srcip[j + temp[2]] >= '0' && srcip[j + temp[2]] <= '9')
          {
              //�е㶫����temp 0��1����������temp 2������λ�á�
              temp[0] = (int)srcip[j + temp[2]] - 48;
              temp[1] = temp[1] * 10 + temp[0];
          }
         else
         {
           //��������ʱj�Լ�1Ŀ������temp[2]+jָ����һ�ֽڵĵ�һλ
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
	//0-6��32-38
    int k = 0,temp[3];
    for (int i = 0; i < 18; i = i + 3){
          temp[0] = (int)desmac[i];
          temp[1] = (int)desmac[i + 1];
          if (temp[0] > 96)         //������macΪСд��ĸʱ�ַ�ת��Ϊ16����
               temp[0] = temp[0] - 87;
          else if (temp[0] > 64)
               temp[0] = temp[0] - 55;//������macΪ��д��ĸʱ�ַ�ת��Ϊ16����
          else
                temp[0] = temp[0] - 48;//������macΪ����ʱ�ַ�ת��Ϊ16����
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
    //Ŀ��ip��38-42
    int k = 0, temp[3], j;
    temp[2] = 0;  //ָ��ÿ���ֽڳ�ʼλ��
    for (int i = 0; i < 4; i++)
    {
        temp[0] = 0;
        temp[1] = 0;
        for (j = 0; j < 4; j++)
        {
            if (desip[j + temp[2]] >= '0' && desip[j + temp[2]] <= '9')
            {
                //�е㶫����temp 0��1����������temp 2������λ�á�
                temp[0] = (int)desip[j + temp[2]] - 48;
                temp[1] = temp[1] * 10 + temp[0];
            }
            else
            {
                //��������ʱj�Լ�1Ŀ������temp[2]+jָ����һ�ֽڵĵ�һλ
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
    //��������������
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
    //����ѭ�������ͼ��
    for (int n = 0; n < num; n++) {
        int i = 0;
        for (d = alldevs; i < numofdevs; d = d->next, i++) {
            adhandle = pcap_open_live(d->name, //�豸�� 
                65536, // ���׽�ֽ��� 
                1, // ����ģʽ 
                1000, // ���볬ʱ 
                errbuf // ���󻺳� 
            );
            pcap_sendpacket(adhandle, packet, 64);
            pcap_close(adhandle);
        }
        Sleep(10*time);
    }
    pcap_freealldevs(alldevs);
}
