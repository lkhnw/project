#pragma once
class ARPbuild
{
public :
	u_char packet[100];
	void sendarp(char* srcmac,char* srcip,char* desmac,char* desip,int num,int time);
	void init();
	void set_srcmac(char* srcmac);
	void set_srcip(char* srcip);
	void set_desmac(char* desmac);
	void set_desip(char* desip);
	void set_else(int num, int time);
};

