
#include "pch.h"
#include"function.h"

char* CaesarEncryption(char* txt, int key) {
	int i = 0;
	char* result = (char*)malloc(sizeof(txt) + sizeof(char));
	while (txt[i] != '\0') {
		if ('A' <= txt[i] && txt[i] <= 'Z') {
			result[i] = (txt[i] - 'A' + key + 26) % 26 + 'A';
		}
		else if ('a' <= txt[i] && txt[i] <= 'z') {
			result[i] = (txt[i] - 'a' + key + 26) % 26 + 'a';
		}
		else {
			result[i] = txt[i];
		}
		i++;
	}
	result[i] = '\0';
	return result;
}
char* CaesarDecryption(char* txt, int key) {
	return CaesarEncryption(txt, (-1) * key);
}
char* CaesarEncryption_str(char* txt, char* key) {
	return CaesarEncryption(txt, sizeof(key) / sizeof(char));
}
char* CaesarDecryption_str(char* txt, char* key) {
	int i = sizeof(key) / sizeof(char);
	return CaesarEncryption(txt, i * (-1));
}

char* VigenereEncryption(char* txt, char* key) {
	int keylen = strlen(key);
	if (keylen == 0) { return txt; }
	int txtlen = strlen(txt);
	char* result = (char*)malloc(sizeof(char) * (txtlen + 1));
	result[txtlen] = '\0';
	int i = 0;
	while (txt[i] != '\0') {
		if ('A' <= txt[i] && txt[i] <= 'Z') {
			result[i] = ((txt[i] - 'A') + (key[i % keylen] - 'a') + 26) % 26 + 'A';
		}
		else if ('a' <= txt[i] && txt[i] <= 'z') {
			result[i] = ((txt[i] - 'a') + (key[i % keylen] - 'a') + 26) % 26 + 'a';
		}
		else {
			result[i] = txt[i];
		}
		i++;
	}
	result[i] = '\0';
	return result;
}
char* VigenereDecryption(char* txt, char* key) {
	int keylen = strlen(key);
	if (keylen == 0) { return txt; }
	int txtlen = strlen(txt);

	char* dekey = (char*)malloc(sizeof(char) * (keylen + 1));
	for (int i = 0; i < keylen; i++) {
		dekey[i] = 'z' - key[i] + 'a' + 1;
	}
	dekey[keylen] = '\0';
	char* result = VigenereEncryption(txt, dekey);
	free(dekey);
	return result;
}


char* OrganizeTxt(char* txt, int txtlen, int* resultlen) {
	//要全小写，去符号。     两两分组去重（插入X且不更改）。
	char* result = (char*)malloc(2 * (txtlen + 1) * sizeof(char));//存结果
	char* temp = (char*)malloc((txtlen + 1) * sizeof(char));//存小写后和去无效符号后
	int j = 0, i;//指向结果char数组的。
	for (i = 0; i < txtlen; i++) {
		if ('A' <= txt[i] && txt[i] <= 'Z') {
			temp[j] = txt[i] - 'A' + 'a';
			if (temp[j] == 'j') { temp[j] = 'i'; }
			j++;
		}
		else if ('a' <= txt[i] && txt[i] <= 'z') {
			temp[j] = txt[i];
			if (temp[j] == 'j') { temp[j] = 'i'; }
			j++;
		}
		else {
			//无效符号，啥都不干。改了直接添加
			temp[j] = txt[i];
			j++;
		}
	}
	temp[j] = '\0';
	int k, relo = 0;
	for (k = 0; k < j; k = k + 2) {
		result[relo] = temp[k];
		relo++;
		if (temp[k + 1] == temp[k] || temp[k + 1] == '\0') {
			result[relo] = 'x';
			relo++;
			k--;
		}
		else {
			result[relo] = temp[k + 1];
			relo++;
		}
	}
	result[relo] = '\0';
	*resultlen = relo;
	return result;
}
char* OrganizeKey(char* key, int keylen, int* resultlen) {
	char rm = 'j';

	char* temp = (char*)malloc((keylen + 1) * sizeof(char));//存小写后和去无效符号后
	int j = 0, i;//指向结果char数组的。
	for (i = 0; i < keylen; i++) {
		if ('A' <= key[i] && key[i] <= 'Z') {
			temp[j] = key[i] - 'A' + 'a';
			j++;
		}
		else if ('a' <= key[i] && key[i] <= 'z') {
			temp[j] = key[i];
			j++;
		}
		else {
			//无效符号，啥都不干。
		}
	}
	temp[j] = '\0';
	char* result = (char*)malloc(sizeof(char) * j);
	int relen = 0, sign[26] = {};
	for (int i = 0; i < j; i++) {
		//temp[i]到sign标记查看，确定加入密钥还是抛弃。
		if (sign[temp[i] - 'a'] == 0) {
			result[relen] = temp[i];
			relen++;
			sign[temp[i] - 'a'] = 1;
		}
	}
	result[relen] = '\0';
	*resultlen = relen;
	return result;
}
CooXY* PlayfairMap(char* realkey, int keylen, char lettermap[5][5]) {
	//我需要字母（0-25）到坐标表，和坐标到字母表
	//字母j先占位，最后再与i同步，如果省去的字母是其他，则在这里修改
	//de一般是j,但也可以是其它少用的字符,本来想做多种playfair，想想算了。
	char de = 'j';

	CooXY* map = (CooXY*)malloc(sizeof(CooXY) * 27);
	map[de - 'a'].x = 0;
	map[de - 'a'].y = 0;
	char i = 0;
	while (i < keylen) {
		map[realkey[i] - 'a'].y = i % 5;
		map[realkey[i] - 'a'].x = i / 5;
		lettermap[map[realkey[i] - 'a'].x][map[realkey[i] - 'a'].y] = realkey[i];
		i++;
	}
	for (int j = 0; j < 26; j++) {
		if (map[j].x < 0) {
			map[j].y = i % 5;
			map[j].x = i / 5;
			lettermap[map[j].x][map[j].y] = j + 'a';
			i++;
		}
	}
	map[9].x = map[8].x;
	map[9].y = map[8].y;
	return map;
}
char* PlayfairEncryption(char* txt ,char* key) {
	int txtlen = strlen(txt);
	int keylen = strlen(key);
	if (keylen == 0) { return txt; }

	char* realtxt; int realtxtlen;
	realtxt = OrganizeTxt(txt, txtlen, &realtxtlen);
	//printf("\n%s\n", realtxt);
	char* realkey; int realkeylen;
	realkey = OrganizeKey(key, keylen, &realkeylen);
	char lettermap[5][5];
	CooXY* Map = PlayfairMap(realkey, realkeylen, lettermap);
	int i = 0, resultlen = 0;
	char* result = (char*)malloc(sizeof(char) * (realtxtlen + 1));
	for (i = 0; i < realtxtlen; i = i + 2) {
		if (Map[realtxt[i] - 'a'].x != Map[realtxt[i + 1] - 'a'].x && Map[realtxt[i] - 'a'].y != Map[realtxt[i + 1] - 'a'].y) {
			result[resultlen] = lettermap[Map[realtxt[i + 1] - 'a'].x][Map[realtxt[i] - 'a'].y];
			result[resultlen + 1] = lettermap[Map[realtxt[i] - 'a'].x][Map[realtxt[i + 1] - 'a'].y];
			resultlen = resultlen + 2;
		}
		else if (Map[realtxt[i] - 'a'].y == Map[realtxt[i + 1] - 'a'].y) {//同行
			result[resultlen] = lettermap[(Map[realtxt[i] - 'a'].x + 1) % 5][Map[realtxt[i] - 'a'].y];
			result[resultlen + 1] = lettermap[(Map[realtxt[i + 1] - 'a'].x + 1) % 5][Map[realtxt[i] - 'a'].y];
			resultlen = resultlen + 2;
		}
		else if (Map[realtxt[i] - 'a'].x == Map[realtxt[i + 1] - 'a'].x) {//同列
			result[resultlen] = lettermap[Map[realtxt[i] - 'a'].x][(Map[realtxt[i] - 'a'].y + 1) % 5];
			result[resultlen + 1] = lettermap[Map[realtxt[i] - 'a'].x][(Map[realtxt[i + 1] - 'a'].y + 1) % 5];
			resultlen = resultlen + 2;

		}
	}
	result[realtxtlen] = '\0';
	return result;
}
char* PlayfairDecryption(char* txt, char* key) {
	int txtlen = strlen(txt);
	int keylen = strlen(key);
	if (keylen == 0) { return txt; }


	char* realtxt; int realtxtlen;
	realtxt = OrganizeTxt(txt, txtlen, &realtxtlen);
	//printf("\n%s\n", realtxt);
	char* realkey; int realkeylen;
	realkey = OrganizeKey(key, keylen, &realkeylen);
	char lettermap[5][5];
	CooXY* Map = PlayfairMap(realkey, realkeylen, lettermap);
	int i = 0, resultlen = 0;
	char* result = (char*)malloc(sizeof(char) * (realtxtlen + 1));
	for (i = 0; i < realtxtlen; i = i + 2) {
		if (Map[realtxt[i] - 'a'].x != Map[realtxt[i + 1] - 'a'].x && Map[realtxt[i] - 'a'].y != Map[realtxt[i + 1] - 'a'].y) {
			result[resultlen] = lettermap[Map[realtxt[i + 1] - 'a'].x][Map[realtxt[i] - 'a'].y];
			result[resultlen + 1] = lettermap[Map[realtxt[i] - 'a'].x][Map[realtxt[i + 1] - 'a'].y];
			resultlen = resultlen + 2;
		}
		else if (Map[realtxt[i] - 'a'].y == Map[realtxt[i + 1] - 'a'].y) {//同行
			result[resultlen] = lettermap[(Map[realtxt[i] - 'a'].x - 1 + 5) % 5][Map[realtxt[i] - 'a'].y];
			result[resultlen + 1] = lettermap[(Map[realtxt[i + 1] - 'a'].x - 1 + 5) % 5][Map[realtxt[i] - 'a'].y];
			resultlen = resultlen + 2;
		}
		else if (Map[realtxt[i] - 'a'].x == Map[realtxt[i + 1] - 'a'].x) {//同列
			result[resultlen] = lettermap[Map[realtxt[i] - 'a'].x][(Map[realtxt[i] - 'a'].y - 1 + 5) % 5];
			result[resultlen + 1] = lettermap[Map[realtxt[i] - 'a'].x][(Map[realtxt[i + 1] - 'a'].y - 1 + 5) % 5];
			resultlen = resultlen + 2;

		}
	}
	result[realtxtlen] = '\0';
	return result;
}

int* getColRealKey(char* key, int keylen) {
	int* order = (int*)malloc(sizeof(int) * keylen);
	//得顺序密钥
	for (int i = 0; i < keylen; i++) {
		order[i] = 1;
	}
	for (int i = 0; i < keylen; i++) {
		for (int j = i + 1; j < keylen; j++) {
			if (key[i] > key[j]) { order[i]++; }
			else { order[j]++; }
		}
	}
	return order;
}
char** gettxtmatrix(char* txt, int txtlen, int keylen, int* recollen, int* rerowlen) {
	int rowlen = keylen;
	int collen = txtlen / keylen;
	if (collen * keylen < txtlen) {
		collen++;
	}
	char** retxtmatrix = (char**)malloc(sizeof(char*) * collen);
	for (int i = 0; i < collen; i++) {
		retxtmatrix[i] = (char*)malloc(sizeof(char) * rowlen);
	}
	int k = 0;
	for (int i = 0; i < collen; i++) {
		for (int j = 0; j < rowlen; j++) {
			if (k < txtlen) {
				retxtmatrix[i][j] = txt[k];
				k++;
			}
			else { retxtmatrix[i][j] = ' '; }
		}
	}
	*recollen = collen; *rerowlen = rowlen;
	return retxtmatrix;
}
char* getresult(char** txtmatrix, int collen, int rowlen, int* realkey) {
	char* result = (char*)malloc(sizeof(char) * (collen * rowlen + 1));
	for (int i = 0; i < rowlen; i++) {
		for (int j = 0; j < collen; j++) {
			result[(realkey[i] - 1) * collen + j] = txtmatrix[j][i];
		}
	}
	result[collen * rowlen] = '\0';
	return  result;
}
char* ColumnpermutationEncryption(char* txt, char* key) {
	int txtlen = strlen(txt); int keylen = strlen(key);
	int* realkey = getColRealKey(key, keylen);
	int collen = 0, rowlen = 0;
	char** txtmatrix = gettxtmatrix(txt, txtlen, keylen, &collen, &rowlen);
	char* result = getresult(txtmatrix, collen, rowlen, realkey);
	return result;
}
char* ColumnpermutationDecryption(char* cryp, char* key) {
	int cryplen = strlen(cryp); int keylen = strlen(key);
	int* realkey = getColRealKey(key, keylen);
	int collen = cryplen / keylen;
	int rowlen = keylen;
	if (collen * keylen < cryplen) { collen++; }
	char** a = retxtmatrix(cryp, cryplen, collen, rowlen, realkey);
	char* txt = gettxt(a, collen, rowlen);
	return txt;
}
char** retxtmatrix(char* cryp, int cryplen, int collen, int rowlen, int* realkey) {
	char** txtmatrix = (char**)malloc(sizeof(char*) * collen);
	for (int i = 0; i < collen; i++) {
		txtmatrix[i] = (char*)malloc(sizeof(char) * rowlen);
	}
	for (int i = 0; i < rowlen; i++) {
		for (int j = 0; j < collen; j++) {
			if ((realkey[i] - 1) * collen + j < cryplen) {
				txtmatrix[j][i] = cryp[(realkey[i] - 1) * collen + j];
			}
			else { txtmatrix[j][i] = ' '; }
		}
	}
	return txtmatrix;
}
char* gettxt(char** matrix, int collen, int rowlen) {
	char* txt = (char*)malloc(sizeof(char) * (collen * rowlen + 1));
	int k = 0;
	for (int i = 0; i < collen; i++) {
		for (int j = 0; j < rowlen; j++) {
			txt[k] = matrix[i][j];
			k++;
		}
	}
	txt[k] = '\0';
	return txt;
}


/*初始化函数*/
void rc4_init(unsigned char* s, unsigned char* key, unsigned long Len)
{
	int i = 0, j = 0;
	char k[256] = { 0 };
	unsigned char tmp = 0;
	for (i = 0; i < 256; i++)
	{
		s[i] = i;
		k[i] = key[i % Len];
	}
	for (i = 0; i < 256; i++)
	{
		j = (j + s[i] + k[i]) % 256;
		tmp = s[i];
		s[i] = s[j];//交换s[i]和s[j]
		s[j] = tmp;
	}
}

/*加解密*/
void rc4_crypt(unsigned char* s, unsigned char* Data, unsigned long Len)
{
	int i = 0, j = 0, t = 0;
	unsigned long k = 0;
	unsigned char tmp;
	for (k = 0; k < Len; k++)
	{
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		tmp = s[i];
		s[i] = s[j];//交换s[x]和s[y]
		s[j] = tmp;
		t = (s[i] + s[j]) % 256;
		Data[k] ^= s[t];
	}
	Data[k] = '\0';
}

char* rc4en(char* txt0, char* key0)
{
	unsigned char s[256] = { 0 }, s2[256] = { 0 };
	char key[256];
	int key0len = strlen(key0);
	for (int i = 0; i < key0len && i < 256; i++) {
		key[i] = key0[i];
	}
	unsigned long len = strlen(txt0);
	int i;
	rc4_init(s, (unsigned char*)key, key0len);
	char* result = txt0;
	rc4_crypt(s, (unsigned char*)result, len);//加密
	//printf("pDatas=\n%s\n\n", pData);
	return result;
}

char* rc4de(char* txt0, char* key0) {
	return rc4en(txt0, key0);
}


