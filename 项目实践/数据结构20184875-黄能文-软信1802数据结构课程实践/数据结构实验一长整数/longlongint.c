#include<stdio.h>
#include <stdbool.h>
#include"longlongint.h"
//一个节点存四位数
//构造函数，当然只做了创建空数。
Llintline* creatLlintline() {
	Llintline* line;
	line = (Llintline*)malloc(sizeof(Llintline));
	DBnode* dbnode;
	dbnode = creatDBnode_null();
	line->head = dbnode;
	//1正，-1负
	line->head->nums = 1;
	line->len = 0;
	return line;
}
//链表长度
int len_list(Llintline* line)
{
	return line->len;
}

bool isempty(Llintline* list) {
	return list->len == 0;
}

//
void clear_DBlist(Llintline* line) { line->head = creatDBnode_null(); line->len = 0; }

void addfirstDBnode_Llintline(Llintline* line) {
	if (line->head == NULL) { 
		printf("addfirstDBnode_Llintline处传入了空指针line.head"); 
		return; }
	if (line->len == 0) {
		line->head->next = (Llintline*)malloc(sizeof(Llintline));
		line->head->pre =line->head->next;
		line->head->next->next = line->head;
		line->head->next->pre = line->head;
		line->len++;
	}
	else {
		DBnode* node;
		node = (DBnode*)malloc(sizeof(DBnode));
		node->next = line->head->next;
		node->pre= line->head;
		line->head->next = node;
		node->next->pre = node;
		line->len++;
	}
}

void addfirstDBnode_Llintline_longint(Llintline* head, long num) {
	addfirstDBnode_Llintline(head);
	change(head,1,num);
}
//addlast
void addlastDBnode_Llintline(Llintline* line) {
	if (line->len == 0) {
		line->head->next = (Llintline*)malloc(sizeof(Llintline));
		line->head->pre = line->head->next;
		line->head->next->next = line->head;
		line->head->next->pre = line->head;
		line->len++;
	}else{
		DBnode* node;
		node = (DBnode*)malloc(sizeof(DBnode));
		node->next = line->head;
		node->pre = line->head->pre;
		node->pre->next = node;
		line->head->pre = node;
		line->len ++;
	}
}

void addlastDBnode_Llintline_longint(Llintline* head, long num) {
	addlastDBnode_Llintline(head);
	head->head->pre->nums = num;
}
//删除第一个节点（不是头节点）
void delfirstDBnode(Llintline* line) {
	if (line->len == 0) { return; }
	else {
		line->head->next = line->head->next->next;
		line->head->next->pre->pre = NULL;
		line->head->next->pre->next = NULL;
		line->head->next->pre = line->head;
		line->len--;
	}
}
//注意n=0就没有了，因为头结点被占用了，只有1才是第一个数字。
void change(Llintline* line, int n, int num) {
	if (n > line->len){return;
}
	DBnode* temp;
	temp = line->head;
	int i = 0;
	while (i < n) {
		i++;
		temp = temp->next;
	}
	temp->nums = num;
}
void changefirsthao(Llintline* line) {
	if (line->head->nums < 0) { line->head->nums = 1; }
	else { line->head->nums = (-1); }
}
//tonum仅输出num,先用printf试一下吧
void tonum(Llintline* line) {
	if (line->len <=0)printf("0");
	else if(line->len>1){
		DBnode* temp;
		temp = line->head;
		if (temp->nums <0)printf("-");
		temp = temp->next;
		/*
		if (temp->nums / 1000 ==0) {
			printf("0");
			if (temp->nums / 100 == 0) {
				printf("0");
				if(temp->nums/10==0)
					printf("0");
			}
		}
		*/
		printf("%d", temp->nums);
		temp = temp->next;
		while (temp!= line->head)
		{
			printf(",");
			if (temp->nums / 1000 == 0) {
				printf("0");
				if (temp->nums / 100 == 0) {
					printf("0");
					if (temp->nums / 10 == 0)
						printf("0");
				}
			}
			printf("%d", temp->nums);
			temp = temp->next;
		}
	}
	else { if (line->head->nums < 0){printf("-"); }
			printf("%d", line->head->next->nums);
}
}

//加法，先做一个纯数字部分的加法和减法，再让包括符号的数字调用。
	//不管怎么样都需要一个新的链表保存数
	//先想想人会怎么做，首先肯定和长度有关，长度为0代表0，那就返回另一个就好了。
	//长度都不为0，那就有的加了，从末尾开始取两块相加。
	//判断结果是否溢出，溢出则-10000，然后溢出int置1
	//判断长度，都还有数，则取下一块相加后再加上溢出int，int置0，判断是否溢出，如果溢出，则溢出位置1。
	//总有数会到尽头，结果addfirst另外一个数的当前节点值加上溢出int和往前的节点，直到也结束。
	//返回结果。
Llintline* unsightnumsadd(Llintline* nums1, Llintline* nums2) {
	Llintline* result;
	result = creatLlintline();
	int len1 = nums1->len, len2 = nums2->len;
	int jinwei=0;
	DBnode* temp1=creatDBnode_null(), *temp2=creatDBnode_null();
	if (len1 == 0 && len2 == 0) { return result; }
	else {
		if (len1 != 0) {
			temp1 = nums1->head->pre;
		}
		if (len2 != 0) {
			temp2 = nums2->head->pre;
		}
	}
	
	int up=0;
	while (true) {
		//退出条件,判断的是加到哪了，其中一个数加完了，就走复制了。
		//
		if (len1 == 0) {
			for (int i = len2; i >0; i--) {
				long cur = temp2->nums + jinwei;
				jinwei = 0;
				if (cur > 10000) {
					jinwei = 1;
					cur = cur - 10000;
				}
				addfirstDBnode_Llintline_longint(result, cur);
				temp2 = temp2->pre;
			}
			if (jinwei == 1) { addfirstDBnode_Llintline_longint(result, 1); jinwei = 0; }
			return result;
		}
		//
		else if (len2 == 0) {
			for (int i = len1; i > 0; i--) {
				long cur = temp1->nums + jinwei;
				jinwei = 0;
				if (cur > 10000) {
					jinwei = 1;
					cur = cur - 10000;
				}
				addfirstDBnode_Llintline_longint(result, cur);
				temp1 = temp1->pre;
			}
			if (jinwei == 1) { addfirstDBnode_Llintline_longint(result, 1); jinwei = 0; }
			return result;
		}else{//一般情况，主循环
			long cur = temp1->nums + temp2->nums + jinwei;
			jinwei = 0;
			if (cur > 10000) {
				jinwei = 1;
				cur = cur - 10000;
			}
			addfirstDBnode_Llintline_longint(result, cur);
			temp1 = temp1->pre;
			temp2 = temp2->pre;
			len1--;
			len2--;
		}
	}

}

//无符号减法
	//思路？直接减法？负数加上10000，进位值-1？
	//去首0？这个应该比较简单，单独做一个化简就好了放在另一各函数里
	//感觉做绝对值好一点，既然都说了无符号了
	//抛弃上面的想法a-b和b-a只差一个负号。
	//做绝对值就要比大小
	//如果不判断大小直接减的话，那最后的负数怎么解决？当然是乘以负一啊。不行不行。
	//还是判断大小吧，首先判断长度，同长度，在判断值，（判断第一节点值，第二节点值等）
	//不难发现，如果节点值相同，那部分也不需要计算，就直接跳过。反正都是0;也不显得浪费
	//跳过方法就是len2和len1减一。
	
Llintline* unsightnumsminus(Llintline* nums1, Llintline* nums2) {
	Llintline* result;
	result = creatLlintline();
	int len1 = nums1->len, len2 = nums2->len;
	int flag;//flag=1表示1大，否则表示2大
	DBnode* tmd1, * tmd2;
	//反人类
	tmd1 = nums1->head->next;
	tmd2 = nums2->head->next;
	//判断
	if (len1 > len2) {
		//走1》2的
		flag = 1;
	}
	else if (len1 == len2) {
		//等长度，反人类的要从前面往后判断大小。
		while (true) {
			if (tmd1->nums == tmd2->nums) { tmd1 = tmd1->next; tmd2->next = tmd2->next; len1--; len2--;
			//假设数字完全一样呢，俩len--后都0了那就返回0吧。
			if (len1 == 0) { return result; }
			}
			else if (tmd1->nums > tmd2->nums) { flag = 1; break; }
			else { flag = 2; break; }
		}
	}else{//走2大于1的
		flag = 2;
	}
	if (flag == 2) { result->head->nums = -1; }
	int jinwei = 0;
	DBnode* temp1, * temp2;
	//从后往前算的加法
	temp1 = nums1->head->pre;
	temp2 = nums2->head->pre;


	while (true) {
		//退出条件,判断的是加到哪了，其中一个数加完了，就走复制了。
		//小的那部分被减完了，剩下的大的也走复制啊。
		//就是两个一样长的时候？len的意义包含在flag里，用flag就OK了
		////其实4种情况，flag=1，len2先到0。flag=2，len1先到0。一起到0反而无所谓（flag1,2重要）。
		//可以总结成一次返回吧，if里面只要cur的计算不同就可以了哦，还有len
		//计算部分的判断循环
			long cur;
			if (flag == 1 && len1>0 && len2>0) {cur = temp1->nums - temp2->nums + jinwei; 
			temp1 = temp1->pre;
			temp2 = temp2->pre;
			len1--;
			len2--;
			}
			else if(flag==2 && len1>0 &&len2>0){ cur = temp2->nums - temp1->nums + jinwei;
			temp1 = temp1->pre;
			temp2 = temp2->pre;
			len1--;
			len2--;
			}
			else if (flag == 1 && len2 <= 0 && len1 > 0) { cur = temp1->nums + jinwei; temp1 = temp1->pre; len1--; }//len=0，flag1，flag2两种
			else if (flag == 2 && len1 <= 0 && len2 > 0) { cur = temp2->nums + jinwei;	temp2 = temp2->pre; len2--; }//如果严谨写else就可以了
			else { return result; }
			//计算结果的判断
			if (cur < 0) {
				jinwei = -1;
				cur = cur + 10000;
			}
			else { jinwei = 0;}
			//将计算结果赋予result
			addfirstDBnode_Llintline_longint(result, cur);
	}

}

//乘法，我服了呀,再做一个long数组吗，用int[8]可以，long[4]可以，前两个进位转化成long，后两个也是转化成long
//虽然基于我这个数据结构做两位乘法具有普适性，但是我不想写了，我就简单写写吧。
//乘加乘加走起，两层循环
Llintline* numsmult(Llintline* nums1, Llintline* nums2) {
	Llintline* result;
	result = creatLlintline();
	Llintline* tempresult;
	tempresult = creatLlintline();
	int len1 = nums1->len, len2 = nums2->len;
	DBnode* temp1, * temp2;
	if (len1 == 0 || len2 == 0) { return result; }
	temp1 = nums1->head->pre;
	temp2 = nums2->head->pre;
	//给cur的进位
	long cur;
	long jinwei=0;
	//下面3个是用于计算的
	long num1[2];
	long num2[2];
	long result_jinwei=0;
	//long curr;
	long result_num[4] = {0,0,0,0};
	for (int i = 0; i < nums1->len; i++) {//左式
		num1[0] = temp1->nums % 100;
		num1[1] = temp1->nums / 100;
		for (int j = 0; j < nums2->len; j++)//右式
		{
			num2[0] = temp2->nums % 100;
			num2[1] = temp2->nums / 100;
			//这部分不能直接longlong相乘
			//老子不循环了，直接算它呀的
			result_num[0] = (num1[0] * num2[0]) % 100;
			result_jinwei= (num1[0] * num2[0]) / 100;
			result_num[1] = (num1[1] * num2[0]+ num1[0] * num2[1]+ result_jinwei) % 100;
			result_jinwei = (num1[1] * num2[0] + num1[0] * num2[1] + result_jinwei) / 100;
			result_num[2] = ((num1[1] * num2[1])+result_jinwei)%100;
			result_jinwei = ((num1[1] * num2[1]) + result_jinwei)/100;
			result_num[3]=  result_jinwei%100;

			cur=result_num[0]+result_num[1]*100+jinwei;
			jinwei = result_num[2]+result_num[3]*100;
			if (cur >= 10000) { cur = cur - 10000; jinwei = jinwei + 1; }
			temp2 = temp2->pre;
			//这个结果不是乘法的结果，只作为加法的一部分。
			addfirstDBnode_Llintline_longint(tempresult, cur);
			//所有的cur加完了还得考虑下jinwei存在数。
		}
		//接在add完所有cur之后
		addfirstDBnode_Llintline_longint(tempresult, jinwei);
		jinwei = 0;
		//给加法的部分加权，即在最后补0节点，补的节点数和i相关
		for (int k = 0; k < i; k++) {
			addlastDBnode_Llintline_longint(tempresult, 0);
		}
		//做加法注意了这是无符号加法，所以不管怎么乘从这里出去的都是正的。
		tempresult = qushouzero(tempresult);
		result=unsightnumsadd(tempresult,result);
		clear_DBlist(tempresult);
		temp1 = temp1->pre;
		//temp2还要重置啊
		temp2= nums2->head->pre;
	}
	//输出
	//确定符号在这里
	result->head->nums = nums1->head->nums * nums2->head->nums;
	return result;
}

Llintline* numsadd(Llintline* nums1, Llintline* nums2) {
	Llintline* result;
	result = (Llintline*)malloc(sizeof(Llintline));
	//四种情况，分清楚符号和数字。同号加，异号减。前负负，前正正（啥都不用干）。
	if (nums1->head->nums * nums2->head->nums > 0) { result = unsightnumsadd(nums1, nums2); }
	else{result = unsightnumsminus(nums1, nums2);}
	if (nums1->head->nums < 0) { result->head->nums = result->head->nums * (-1); }
	return result;
}

Llintline* numsminus(Llintline* nums1, Llintline* nums2) {
	Llintline* result;
	result = (Llintline*)malloc(sizeof(Llintline));
	//四种情况，分清楚符号和数字。同号减，异号加。前负负，前正正（啥都不用干）。
	if (nums1->head->nums * nums2->head->nums > 0) {
		result = unsightnumsminus(nums1, nums2); }
	else { result = unsightnumsadd(nums1, nums2); }
	if (nums1->head->nums < 0) { result->head->nums = result->head->nums * (-1); }
	return result;
}

Llintline* stringtonum(char* a ,int le) {
	int c, b;
	Llintline* line = creatLlintline();
	int isfuhao;
	//判断有没符号
	char f[2]="-+";
	if (a[0] == f[0]) { 
		line->head->nums = -1;  
		isfuhao = 1; }
	else if (a[0] == f[1]) { isfuhao = 1; }
	else { isfuhao = 0; }
	//强转long
	//分成两部分，4位数节点，和不满四位数节点的开头部分
	//寻址，加权循环次数在0到c之间，用i继承，le-4*（i+1）到le-i*4之间，用j继承，temp和j的关系，temp【0】对应a【j-（le-4*（i+1））】取数
	//long=temp【0】*1000+。。。100。。。10.。；
	c = (le - isfuhao) / 4;
	b = (le - isfuhao) % 4;
	long cur=0;
	long temp[4] = { 0,0,0,0 };
	char fuhao0[1] = "0";
	for (int i = 0; i < c; i++) {
		for (int j = le - 4 * (i+1); j < le - 4 * i; j++) {
			temp[j - (le - 4 * i - 4)] = (long)(a[j]-fuhao0[0]);
		}
		long cur = temp[0] * 1000 + temp[1] * 100 + temp[2] * 10 + temp[3];
		temp[0] = temp[1] = temp[2] = temp[3] = 0;
		addfirstDBnode_Llintline_longint(line, cur);
		cur = 0;
	}
	//cur = a[b]+a[b-1]*10....a[isfuhao]*10^(b-isfuhao)
	//b是数字部分的长度余数
	//直接转化吧a[isfuhao]加权1，a[isfuhao+1]加权10，直到b
	if (b == 0) { return line; }
	else {
		for (int i = 0; i < b; i++) {
			temp[i] = (long)(a[isfuhao + i] - fuhao0[0]);
		}
		//对每位数加权，从第一位加权10的b-1-i次方开始，当i=b结束
		//原地加权的方法，可以和上面的循环合起来。
		for (int i = 0; i < b; i++) {//b个数字
			for (int j = 0; j < b - i - 1; j++)//第i个数字加权10的b-i-1次
				temp[i] = temp[i] * 10;
			cur = cur + temp[i];
		}
		addfirstDBnode_Llintline_longint(line, cur);
		return line;
	}
}

//前闭，后开吧 
Llintline* stringtonum_doubleindex(char* a, int star, int over) {
	if (star > over) { return NULL; }
	else if (star == over) { return NULL; }
	//虽然写在这个数据结构里，但是显然，只要切去前面的长度就可以了，属于string的操作
	char* aa;
	aa = (char*)malloc(sizeof(char)*(over-star));//分配\0了没？看情况要不要+1.
	for (int i = 0; i < over - star; i++) {
		aa[i] = a[i + star];
	}
	return stringtonum(aa, over - star);
}

//去首0应用于乘法产生的冗余
Llintline* qushouzero(Llintline* line) {
	if (line->len == 0) { return line; }
	while (true) {
		if (line->head->next->nums == 0 && line->len>1) { 
			delfirstDBnode(line);
		}
		else { break; }
	}
	return line;
}

