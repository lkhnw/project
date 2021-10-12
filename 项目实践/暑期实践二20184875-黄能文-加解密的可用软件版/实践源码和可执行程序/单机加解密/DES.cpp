#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "pch.h"
#include"DES.h"

//函数声明 
void HexToBit(bool* DatOut, char* DatIn, int Num);							//十六进制转二进制 
void BitCopy(bool* DatOut, bool* DatIn, int Num); 							//数组复制 
void Table_change(bool* DatOut, bool* DatIn, const int* Table, int Num);		//表置换函数 
void LoopMove(bool* DatIn, int Len, int Num);									//子密钥生成中的轮移位函数 
void SetKey(bool* KeyBit);													//生成子密钥的函数 
void Xor(bool* DatA, bool* DatB, int Num);									//异或函数 
void S_change(bool* DatOut, bool* DatIn); 									//S盒变换 
void IntToBit(bool* DatOut, int DatIn, int Num);								//将数据转成二进制 
void F_change(bool* Out, bool* Ri_, int Num); 								//F变换 
void BitToHex(char* DatOut, bool* DatIn, int Num);							//二进制转十六进制 
void Reverse(bool* Li, bool* Ri, int num);									//十六轮迭代之后的左右交换函数		
void Encrypt(bool* CipherBit, bool PlainBit[64], bool KeyBit[64]);			//一个64bit分组的加密过程 
void Decrypt(bool* DecryptBit, bool CipherBit[64], bool KeyBit[64]);			//一个64bit分组的解密过程 
/*测试函数，输出二进制数组*/
void OutBit(bool Bit[], int num) {
	int i;
	for (i = 0; i < num; i++) printf("%d", Bit[i]);
	printf("\n");
}

char* chstohex(char* ch);
char* hextochs(char* ch);

void Decrypt(bool* DecryptBit, bool CipherBit[64], bool KeyBit[64])
{
	static bool tmpCipher[64] = { 0 };				//缓存，防止改变CipherBit以影响CBC模式中的解密过程 
	Table_change(tmpCipher, CipherBit, IP, 64);	//IP初始置换 
	SetKey(KeyBit);
	static bool* CiL = &tmpCipher[0], * CiR = &tmpCipher[32];	//将密文分为L,R两半
	static bool Temp[32] = { 0 };	//缓存
	for (int i = 15; i >= 0; i--)	//16轮变换
	{
		BitCopy(Temp, CiR, 32);
		F_change(CiR, CiR, i);
		Xor(CiR, CiL, 32);
		BitCopy(CiL, Temp, 32);
	}
	Reverse(CiL, CiR, 32);
	Table_change(DecryptBit, tmpCipher, IPR, 64); 	//初始逆置换 
}

void Encrypt(bool* CipherBit, bool PlainBit[64], bool KeyBit[64])		//一个分组的加密过程 
{
	Table_change(PlainBit, PlainBit, IP, 64);	//IP初始置换 
	SetKey(KeyBit);	//生成16个密钥 
	static bool* PiL = &PlainBit[0], * PiR = &PlainBit[32];	//将明文分为L,R两半
	static bool Temp[32] = { 0 };	//缓存
	for (int i = 0; i < 16; i++)	//16轮变换
	{
		BitCopy(Temp, PiR, 32);
		F_change(PiR, PiR, i);
		Xor(PiR, PiL, 32);
		BitCopy(PiL, Temp, 32);
	}
	Reverse(PiL, PiR, 32);
	Table_change(CipherBit, PlainBit, IPR, 64); 	//初始逆置换 
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
			tmp[i] = value + '7';       //  余数大于9时处理 10-15 to A-F
		}
		else
		{
			tmp[i] = value + '0';       //  输出字符	   
		}
	}
	strcpy_s(DatOut,100, tmp);

}

void F_change(bool* Out, bool* Ri_, int Num) 	//Num第几轮变换 
{
	bool Temp[48] = { 0 };
	Table_change(Temp, Ri_, E, 48);	//E扩展
	Xor(Temp, SubKey[Num], 48);
	S_change(Temp, Temp);	//S盒变换 
	Table_change(Out, Temp, P, 32);	//P置换 
}
void S_change(bool* DatOut, bool* DatIn)	//输入48位，输出32位
{
	int i = 0, X, Y;
	bool Temp[32] = { 0 };
	for (i = 0; i < 8; i++)
	{

		Y = ((DatIn[i * 6]) << 1) + (DatIn[i * 6 + 5]);                          // Y代表第几行，X代表第几列 
		X = ((DatIn[i * 6 + 1]) << 3) + ((DatIn[i * 6 + 2]) << 2) + ((DatIn[i * 6 + 3]) << 1) + (DatIn[i * 6 + 4]);	//通过移位运算进行定位 
		IntToBit(&Temp[i * 4], S_Box[i][Y][X], 4);	//将找到的数换为二进制 

	}
	BitCopy(DatOut, Temp, 32);	//输出 
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
	int i = 0;                        // 字符型输入 
	for (i = 0; i < Num; i++)
	{

		if ((DatIn[i / 4]) > '9')         //  大于9 
		{
			DatOut[i] = bool((((DatIn[i / 4] - '7') % 16) << (i % 4)) & 0x08);
		}
		else
		{
			DatOut[i] = bool(((DatIn[i / 4] - '0') << (i % 4)) & 0x08);
		}
	}
}

void Xor(bool* DatA, bool* DatB, int Num)           // 异或函数
{
	int i = 0;
	for (i = 0; i < Num; i++)
	{
		DatA[i] = DatA[i] ^ DatB[i];                  // 异或 
	}
}

void SetKey(bool* KeyBit)
{
	bool Temp[56] = { 0 };			//设置缓存，以免改变KeyBit而影响后面的解密 
	Table_change(Temp, KeyBit, PC1, 56);
	bool* KiL = &Temp[0], * KiR = &Temp[28];
	for (int i = 0; i < 16; i++) {
		LoopMove(KiL, 28, LS[i]);
		LoopMove(KiR, 28, LS[i]);
		Table_change(SubKey[i], Temp, PC2, 48);
	}
}

void LoopMove(bool* DatIn, int Len, int num) // 循环左移 Len数据长度 Num移动位数
{
	bool tmp[56] = { 0 };    					// 缓存  
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
		Tmp[i] = DatIn[Table[i] - 1];	//把原来的数据按表中的位置放在Temp内 
	}
	BitCopy(DatOut, Tmp, Num);       // 把缓存Temp的值输出 
}
char* ECB_encrypt(char* txt0, char* key0)//16进制的字符  		//ECB加密函数
{
	char* txt16 = chstohex(txt0);
	char* key16 = chstohex(key0);
	char Turn[1] = { 0 };
	int length = strlen(txt16);			//得到明文长度
	int w = 0;
	char* result16 = (char*)malloc(sizeof(char)*(length + 1));
	result16[0] = '\0';
	int flag = 0;
	for (int j = 0; j < ((length + 15) / 16); j++)   //以64bit为一组进行加密， length小于16时+15/16以保证加密一次 
	{
		char Plain[17] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };  //不足补0 
		char Key[17] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };	//密钥 
		char Cipher[17] = { 0 };	//密文
		char Message[17] = { 0 };	//解密后 
		bool PlainBit[64] = { 0 };	//明文二进制
		bool CipherBit[64] = { 0 }; //密文二进制 
		bool KeyBit[64] = { 0 }; 	//密钥二进制 
		bool MessageBit[64] = { 0 };
		int i = 0;
		for (i = 0; i < 16; i++)
		{
			Turn[0] = txt16[i + w * 16];
			if (Turn[0] == '\0') break;//得到文件中16进制形式的明文 
			else Plain[i] = Turn[0];
		}
		w++;
		HexToBit(PlainBit, Plain, 64);	//将16进制的明文转换为二进制
		int key16len = strlen(key16);
		for (int ii = 0; ii < key16len; ii++) {
			Key[ii] = key16[ii];
		}
		Key[16] = '\0';
		HexToBit(KeyBit, Key, 64);				//将16进制的key转为二进制
		Encrypt(CipherBit, PlainBit, KeyBit);		//进行加密
		BitToHex(Cipher, CipherBit, 64);			//将CipherBit转为16进制 
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
char* ECB_decrypt(char* txt0, char* key0)//16进制的字符     //ECB解密函数
{
	char* txt16 = txt0;
	char* key16 = chstohex(key0);
	char Turn[1] = { 0 };
	int length = strlen(txt16);  		//得到16进制密文长度
	int w = 0;
	char* result16 = (char*)malloc(sizeof(char) * length + 16);
	result16[0] = '\0';
	for (int j = 0; j < ((length + 15) / 16); j++)      //64Bit为一组进行多轮解密
	{
		char Plain[17] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };
		char Key[17] = { '0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0' };		//密钥 
		char Cipher[17] = { 0 };	//密文
		bool PlainBit[64] = { 0 };	//明文二进制
		bool CipherBit[64] = { 0 }; //密文二进制 
		bool KeyBit[64] = { 0 }; 	//密钥二进制 
		int i = 0;
		for (i = 0; i < 16; i++)
		{
			Turn[0] = txt16[i + w * 16];
			if (Turn[0] == '\0') break;
			else Plain[i] = Turn[0];
		}
		w++;
		HexToBit(PlainBit, Plain, 64);	//将16进制的明文转换为二进制

		int key16len = strlen(key16);
		for (int ii = 0; ii < key16len; ii++) {
			Key[ii] = key16[ii];
		}
		Key[16] = '\0';
		HexToBit(KeyBit, Key, 64);		//将16进制的key转为二进制
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

	return ascii;                    // ascii 返回之前未释放
}
// 函数输入16进制字符串，输出对应的字符串
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

	return chs;            // chs 返回前未释放
}
