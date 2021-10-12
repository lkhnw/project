#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "pch.h"
#include"DES.h"

//�������� 
void HexToBit(bool* DatOut, char* DatIn, int Num);							//ʮ������ת������ 
void BitCopy(bool* DatOut, bool* DatIn, int Num); 							//���鸴�� 
void Table_change(bool* DatOut, bool* DatIn, const int* Table, int Num);		//���û����� 
void LoopMove(bool* DatIn, int Len, int Num);									//����Կ�����е�����λ���� 
void SetKey(bool* KeyBit);													//��������Կ�ĺ��� 
void Xor(bool* DatA, bool* DatB, int Num);									//����� 
void S_change(bool* DatOut, bool* DatIn); 									//S�б任 
void IntToBit(bool* DatOut, int DatIn, int Num);								//������ת�ɶ����� 
void F_change(bool* Out, bool* Ri_, int Num); 								//F�任 
void BitToHex(char* DatOut, bool* DatIn, int Num);							//������תʮ������ 
void Reverse(bool* Li, bool* Ri, int num);									//ʮ���ֵ���֮������ҽ�������		
void Encrypt(bool* CipherBit, bool PlainBit[64], bool KeyBit[64]);			//һ��64bit����ļ��ܹ��� 
void Decrypt(bool* DecryptBit, bool CipherBit[64], bool KeyBit[64]);			//һ��64bit����Ľ��ܹ��� 
/*���Ժ������������������*/
void OutBit(bool Bit[], int num) {
	int i;
	for (i = 0; i < num; i++) printf("%d", Bit[i]);
	printf("\n");
}

char* chstohex(char* ch);
char* hextochs(char* ch);

void Decrypt(bool* DecryptBit, bool CipherBit[64], bool KeyBit[64])
{
	static bool tmpCipher[64] = { 0 };				//���棬��ֹ�ı�CipherBit��Ӱ��CBCģʽ�еĽ��ܹ��� 
	Table_change(tmpCipher, CipherBit, IP, 64);	//IP��ʼ�û� 
	SetKey(KeyBit);
	static bool* CiL = &tmpCipher[0], * CiR = &tmpCipher[32];	//�����ķ�ΪL,R����
	static bool Temp[32] = { 0 };	//����
	for (int i = 15; i >= 0; i--)	//16�ֱ任
	{
		BitCopy(Temp, CiR, 32);
		F_change(CiR, CiR, i);
		Xor(CiR, CiL, 32);
		BitCopy(CiL, Temp, 32);
	}
	Reverse(CiL, CiR, 32);
	Table_change(DecryptBit, tmpCipher, IPR, 64); 	//��ʼ���û� 
}

void Encrypt(bool* CipherBit, bool PlainBit[64], bool KeyBit[64])		//һ������ļ��ܹ��� 
{
	Table_change(PlainBit, PlainBit, IP, 64);	//IP��ʼ�û� 
	SetKey(KeyBit);	//����16����Կ 
	static bool* PiL = &PlainBit[0], * PiR = &PlainBit[32];	//�����ķ�ΪL,R����
	static bool Temp[32] = { 0 };	//����
	for (int i = 0; i < 16; i++)	//16�ֱ任
	{
		BitCopy(Temp, PiR, 32);
		F_change(PiR, PiR, i);
		Xor(PiR, PiL, 32);
		BitCopy(PiL, Temp, 32);
	}
	Reverse(PiL, PiR, 32);
	Table_change(CipherBit, PlainBit, IPR, 64); 	//��ʼ���û� 
}

void Reverse(bool* Li, bool* Ri, int num)
{
	static bool temp[32] = { 0 };
	int i;
	for (i = 0; i < num; i++)
	{
		temp[i] = Li[i];
		Li[i] = Ri[i];
		Ri[i] = temp[i];
	}
}

void BitToHex(char* DatOut, bool* DatIn, int Num)
{
	int i = 0, value;
	char tmp[100] = { 0 };
	for (i = 0; i < Num / 4; i++)
	{
		value = ((DatIn[i * 4]) << 3) + ((DatIn[i * 4 + 1]) << 2) + ((DatIn[i * 4 + 2]) << 1) + (DatIn[i * 4 + 3]);
		if (value > 9)
		{
			tmp[i] = value + '7';       //  ��������9ʱ���� 10-15 to A-F
		}
		else
		{
			tmp[i] = value + '0';       //  ����ַ�	   
		}
	}
	strcpy_s(DatOut,100, tmp);

}

void F_change(bool* Out, bool* Ri_, int Num) 	//Num�ڼ��ֱ任 
{
	bool Temp[48] = { 0 };
	Table_change(Temp, Ri_, E, 48);	//E��չ
	Xor(Temp, SubKey[Num], 48);
	S_change(Temp, Temp);	//S�б任 
	Table_change(Out, Temp, P, 32);	//P�û� 
}
void S_change(bool* DatOut, bool* DatIn)	//����48λ�����32λ
{
	int i = 0, X, Y;
	bool Temp[32] = { 0 };
	for (i = 0; i < 8; i++)
	{

		Y = ((DatIn[i * 6]) << 1) + (DatIn[i * 6 + 5]);                          // Y����ڼ��У�X����ڼ��� 
		X = ((DatIn[i * 6 + 1]) << 3) + ((DatIn[i * 6 + 2]) << 2) + ((DatIn[i * 6 + 3]) << 1) + (DatIn[i * 6 + 4]);	//ͨ����λ������ж�λ 
		IntToBit(&Temp[i * 4], S_Box[i][Y][X], 4);	//���ҵ�������Ϊ������ 

	}
	BitCopy(DatOut, Temp, 32);	//��� 
}

void IntToBit(bool* DatOut, int DatIn, int Num)
{
	int i = 0;
	bool temp[64] = { 0 };
	for (i = 0; i < Num; i++)
	{
		temp[i] = bool(((DatIn) << (i % 4)) & 0x08);
	}
	BitCopy(DatOut, temp, Num);
}


void HexToBit(bool* DatOut, char* DatIn, int Num)
{
	int i = 0;                        // �ַ������� 
	for (i = 0; i < Num; i++)
	{

		if ((DatIn[i / 4]) > '9')         //  ����9 
		{
			DatOut[i] = bool((((DatIn[i / 4] - '7') % 16) << (i % 4)) & 0x08);
		}
		else
		{
			DatOut[i] = bool(((DatIn[i / 4] - '0') << (i % 4)) & 0x08);
		}
	}
}

void Xor(bool* DatA, bool* DatB, int Num)           // �����
{
	int i = 0;
	for (i = 0; i < Num; i++)
	{
		DatA[i] = DatA[i] ^ DatB[i];                  // ��� 
	}
}

void SetKey(bool* KeyBit)
{
	bool Temp[56] = { 0 };			//���û��棬����ı�KeyBit��Ӱ�����Ľ��� 
	Table_change(Temp, KeyBit, PC1, 56);
	bool* KiL = &Temp[0], * KiR = &Temp[28];
	for (int i = 0; i < 16; i++) {
		LoopMove(KiL, 28, LS[i]);
		LoopMove(KiR, 28, LS[i]);
		Table_change(SubKey[i], Temp, PC2, 48);
	}
}

void LoopMove(bool* DatIn, int Len, int num) // ѭ������ Len���ݳ��� Num�ƶ�λ��
{
	bool tmp[56] = { 0 };    					// ����  
	BitCopy(tmp, DatIn, num);
	BitCopy(DatIn, DatIn + num, Len - num);
	BitCopy(DatIn + Len - num, tmp, num);
}


void BitCopy(bool* DatOut, bool* DatIn, int Num)
{
	int i = 0;
	for (i = 0; i < Num; i++)
	{
		DatOut[i] = DatIn[i];
	}
}
void Table_change(bool* DatOut, bool* DatIn, const int* Table, int Num)
{
	static bool Tmp[256] = { 0 };
	int i;
	for (i = 0; i < Num; i++)
	{
		Tmp[i] = DatIn[Table[i] - 1];	//��ԭ�������ݰ����е�λ�÷���Temp�� 
	}
	BitCopy(DatOut, Tmp, Num);       // �ѻ���Temp��ֵ��� 
}
char* ECB_encrypt(char* txt0, char* key0)//16���Ƶ��ַ�  		//ECB���ܺ���
{
	char* txt16 = chstohex(txt0);
	char* key16 = chstohex(key0);
	char Turn[1] = { 0 };
	int length = strlen(txt16);			//�õ����ĳ���
	int w = 0;
	char* result16 = (char*)malloc(sizeof(char)*(length + 1));
	result16[0] = '\0';
	int flag = 0;
	for (int j = 0; j < ((length + 15) / 16); j++)   //��64bitΪһ����м��ܣ� lengthС��16ʱ+15/16�Ա�֤����һ�� 
	{
		char Plain[17] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };  //���㲹0 
		char Key[17] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };	//��Կ 
		char Cipher[17] = { 0 };	//����
		char Message[17] = { 0 };	//���ܺ� 
		bool PlainBit[64] = { 0 };	//���Ķ�����
		bool CipherBit[64] = { 0 }; //���Ķ����� 
		bool KeyBit[64] = { 0 }; 	//��Կ������ 
		bool MessageBit[64] = { 0 };
		int i = 0;
		for (i = 0; i < 16; i++)
		{
			Turn[0] = txt16[i + w * 16];
			if (Turn[0] == '\0') break;//�õ��ļ���16������ʽ������ 
			else Plain[i] = Turn[0];
		}
		w++;
		HexToBit(PlainBit, Plain, 64);	//��16���Ƶ�����ת��Ϊ������
		int key16len = strlen(key16);
		for (int ii = 0; ii < key16len; ii++) {
			Key[ii] = key16[ii];
		}
		Key[16] = '\0';
		HexToBit(KeyBit, Key, 64);				//��16���Ƶ�keyתΪ������
		Encrypt(CipherBit, PlainBit, KeyBit);		//���м���
		BitToHex(Cipher, CipherBit, 64);			//��CipherBitתΪ16���� 
		for (int ff = 0; ff < 16; ff++) {
			result16[flag] = Cipher[ff];
			flag++;
			if (Cipher[ff] == '\0') {
				flag--;
				break;
			}
		}
		result16[flag] = '\0';
		//strcat_s(result16,strlen(Cipher), Cipher);
	}
	return result16;
}
char* ECB_decrypt(char* txt0, char* key0)//16���Ƶ��ַ�     //ECB���ܺ���
{
	char* txt16 = txt0;
	char* key16 = chstohex(key0);
	char Turn[1] = { 0 };
	int length = strlen(txt16);  		//�õ�16�������ĳ���
	int w = 0;
	char* result16 = (char*)malloc(sizeof(char) * length + 16);
	result16[0] = '\0';
	for (int j = 0; j < ((length + 15) / 16); j++)      //64BitΪһ����ж��ֽ���
	{
		char Plain[17] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };
		char Key[17] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };		//��Կ 
		char Cipher[17] = { 0 };	//����
		bool PlainBit[64] = { 0 };	//���Ķ�����
		bool CipherBit[64] = { 0 }; //���Ķ����� 
		bool KeyBit[64] = { 0 }; 	//��Կ������ 
		int i = 0;
		for (i = 0; i < 16; i++)
		{
			Turn[0] = txt16[i + w * 16];
			if (Turn[0] == '\0') break;
			else Plain[i] = Turn[0];
		}
		w++;
		HexToBit(PlainBit, Plain, 64);	//��16���Ƶ�����ת��Ϊ������

		int key16len = strlen(key16);
		for (int ii = 0; ii < key16len; ii++) {
			Key[ii] = key16[ii];
		}
		Key[16] = '\0';
		HexToBit(KeyBit, Key, 64);		//��16���Ƶ�keyתΪ������
		Decrypt(CipherBit, PlainBit, KeyBit);
		BitToHex(Cipher, CipherBit, 64);
		Cipher[16] = '\0';
		strcat_s(result16,16, Cipher);
	}
	char* result = hextochs(result16);
	return result;
}
char* chstohex(char* chs)
{
	char hex[16] = { '0', '1', '2', '3', '4', '5', '6', \
		'7', '8','9', 'A', 'B', 'C', 'D', 'E', 'F'
	};

	int len = strlen(chs);
	char* ascii = NULL;
	ascii = (char*)calloc(len * 3 + 1, sizeof(char));            // calloc ascii

	int i = 0;
	while (i < len)
	{
		ascii[i * 2] = hex[(int)((char)chs[i] / 16)];
		ascii[i * 2 + 1] = hex[(int)((char)chs[i] % 16)];
		++i;
	}

	return ascii;                    // ascii ����֮ǰδ�ͷ�
}
// ��������16�����ַ����������Ӧ���ַ���
char* hextochs(char* ascii)
{
	int len = strlen(ascii);
	if (len % 2 != 0)
		return NULL;
	char* chs = NULL;
	chs = (char*)malloc(sizeof(char) * (len / 2 + 1));
	for (int i = 0; i <= len / 2; i++) {
		chs[i] = '\0';
	}
	int  i = 0;
	int ch[2];
	int j = 0;
	while (i < len)
	{
		if (ascii[i] > 64) {
			ch[0] = ascii[i] % 16 + 9;
		}
		else { ch[0] = ascii[i] % 16; }

		if (ascii[i + 1] > 64) {
			ch[1] = ascii[i + 1] % 16 + 9;
		}
		else { ch[1] = ascii[i + 1] % 16; }

		chs[j] = (char)(ch[0] * 16 + ch[1]);
		j++;
		i += 2;
	}
	chs[j] = '\0';

	return chs;            // chs ����ǰδ�ͷ�
}
