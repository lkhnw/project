#pragma once
#include<stdio.h>
#include <malloc.h>
#include <string.h>
#include <string>
//实践二源码设计
char* CaesarEncryption_str(char* txt, char* key);
char* CaesarEncryption(char* txt, int key);
char* CaesarDecryption_str(char* txt, char* key);
char* CaesarDecryption(char* txt, int key);

char* VigenereEncryption(char* txt, char* key);
char* VigenereDecryption(char* txt, char* key);

char* PlayfairEncryption(char* txt, char* key);
char* PlayfairDecryption(char* txt, char* key);
//返回map[a(即0)]=a的坐标。 和修改了传入的lettermap，lettermap【a的坐标】 = a；
struct Coordinate {
	int x = -1;
	int y = -1;
};
typedef struct Coordinate CooXY;
CooXY* PlayfairMap(char* realkey, int keylen, char lettermap[5][5]);
//所谓分组只是两两一组，不连续重复字母
char* OrganizeTxt(char* txt, int txtlen, int* resultlen);
char* OrganizeKey(char* key, int keylen, int* resultlen);

char* ColumnpermutationEncryption(char* txtstr, char* keystr);
//密钥去重，排序，返回密钥提取出来的信息，密钥序和读取序
int* getColRealKey(char* key, int keylen);
char** gettxtmatrix(char* txt, int txtlen, int keylen, int* recollen, int* rowlen);
char* getresult(char** txtmatrix, int collen, int rowlen, int* realkey);
char** retxtmatrix(char* cryp, int cryplen, int collen, int rowlen, int* realkey);
char* gettxt(char** matrix, int collen, int rowlen);
char* ColumnpermutationDecryption(char* cryp, char* key);


void rc4_init(unsigned char* s, unsigned char* key, unsigned long Len);
void rc4_crypt(unsigned char* s, unsigned char* Data, unsigned long Len);
char* rc4en(char* txt, char* key);
char* rc4de(char* txt0, char* key0);
