#pragma once
#include<stdio.h>
#include <malloc.h>
#include <string.h>
#include <string>
//ʵ����Դ�����
char* CaesarEncryption_str(char* txt, char* key);
char* CaesarEncryption(char* txt, int key);
char* CaesarDecryption_str(char* txt, char* key);
char* CaesarDecryption(char* txt, int key);

char* VigenereEncryption(char* txt, char* key);
char* VigenereDecryption(char* txt, char* key);

char* PlayfairEncryption(char* txt, char* key);
char* PlayfairDecryption(char* txt, char* key);
//����map[a(��0)]=a�����ꡣ ���޸��˴����lettermap��lettermap��a�����꡿ = a��
struct Coordinate {
	int x = -1;
	int y = -1;
};
typedef struct Coordinate CooXY;
CooXY* PlayfairMap(char* realkey, int keylen, char lettermap[5][5]);
//��ν����ֻ������һ�飬�������ظ���ĸ
char* OrganizeTxt(char* txt, int txtlen, int* resultlen);
char* OrganizeKey(char* key, int keylen, int* resultlen);

char* ColumnpermutationEncryption(char* txtstr, char* keystr);
//��Կȥ�أ����򣬷�����Կ��ȡ��������Ϣ����Կ��Ͷ�ȡ��
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
