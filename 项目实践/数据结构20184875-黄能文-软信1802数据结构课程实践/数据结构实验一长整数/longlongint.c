#include<stdio.h>
#include <stdbool.h>
#include"longlongint.h"
//һ���ڵ����λ��
//���캯������Ȼֻ���˴���������
Llintline* creatLlintline() {
	Llintline* line;
	line = (Llintline*)malloc(sizeof(Llintline));
	DBnode* dbnode;
	dbnode = creatDBnode_null();
	line->head = dbnode;
	//1����-1��
	line->head->nums = 1;
	line->len = 0;
	return line;
}
//������
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
		printf("addfirstDBnode_Llintline�������˿�ָ��line.head"); 
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
//ɾ����һ���ڵ㣨����ͷ�ڵ㣩
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
//ע��n=0��û���ˣ���Ϊͷ��㱻ռ���ˣ�ֻ��1���ǵ�һ�����֡�
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
//tonum�����num,����printf��һ�°�
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

//�ӷ�������һ�������ֲ��ֵļӷ��ͼ��������ð������ŵ����ֵ��á�
	//������ô������Ҫһ���µ���������
	//�������˻���ô�������ȿ϶��ͳ����йأ�����Ϊ0����0���Ǿͷ�����һ���ͺ��ˡ�
	//���ȶ���Ϊ0���Ǿ��еļ��ˣ���ĩβ��ʼȡ������ӡ�
	//�жϽ���Ƿ�����������-10000��Ȼ�����int��1
	//�жϳ��ȣ�������������ȡ��һ����Ӻ��ټ������int��int��0���ж��Ƿ�������������������λ��1��
	//�������ᵽ��ͷ�����addfirst����һ�����ĵ�ǰ�ڵ�ֵ�������int����ǰ�Ľڵ㣬ֱ��Ҳ������
	//���ؽ����
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
		//�˳�����,�жϵ��Ǽӵ����ˣ�����һ���������ˣ����߸����ˡ�
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
		}else{//һ���������ѭ��
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

//�޷��ż���
	//˼·��ֱ�Ӽ�������������10000����λֵ-1��
	//ȥ��0�����Ӧ�ñȽϼ򵥣�������һ������ͺ��˷�����һ��������
	//�о�������ֵ��һ�㣬��Ȼ��˵���޷�����
	//����������뷨a-b��b-aֻ��һ�����š�
	//������ֵ��Ҫ�ȴ�С
	//������жϴ�Сֱ�Ӽ��Ļ��������ĸ�����ô�������Ȼ�ǳ��Ը�һ�������в��С�
	//�����жϴ�С�ɣ������жϳ��ȣ�ͬ���ȣ����ж�ֵ�����жϵ�һ�ڵ�ֵ���ڶ��ڵ�ֵ�ȣ�
	//���ѷ��֣�����ڵ�ֵ��ͬ���ǲ���Ҳ����Ҫ���㣬��ֱ����������������0;Ҳ���Ե��˷�
	//������������len2��len1��һ��
	
Llintline* unsightnumsminus(Llintline* nums1, Llintline* nums2) {
	Llintline* result;
	result = creatLlintline();
	int len1 = nums1->len, len2 = nums2->len;
	int flag;//flag=1��ʾ1�󣬷����ʾ2��
	DBnode* tmd1, * tmd2;
	//������
	tmd1 = nums1->head->next;
	tmd2 = nums2->head->next;
	//�ж�
	if (len1 > len2) {
		//��1��2��
		flag = 1;
	}
	else if (len1 == len2) {
		//�ȳ��ȣ��������Ҫ��ǰ�������жϴ�С��
		while (true) {
			if (tmd1->nums == tmd2->nums) { tmd1 = tmd1->next; tmd2->next = tmd2->next; len1--; len2--;
			//����������ȫһ���أ���len--��0���Ǿͷ���0�ɡ�
			if (len1 == 0) { return result; }
			}
			else if (tmd1->nums > tmd2->nums) { flag = 1; break; }
			else { flag = 2; break; }
		}
	}else{//��2����1��
		flag = 2;
	}
	if (flag == 2) { result->head->nums = -1; }
	int jinwei = 0;
	DBnode* temp1, * temp2;
	//�Ӻ���ǰ��ļӷ�
	temp1 = nums1->head->pre;
	temp2 = nums2->head->pre;


	while (true) {
		//�˳�����,�жϵ��Ǽӵ����ˣ�����һ���������ˣ����߸����ˡ�
		//С���ǲ��ֱ������ˣ�ʣ�µĴ��Ҳ�߸��ư���
		//��������һ������ʱ��len�����������flag���flag��OK��
		////��ʵ4�������flag=1��len2�ȵ�0��flag=2��len1�ȵ�0��һ��0��������ν��flag1,2��Ҫ����
		//�����ܽ��һ�η��ذɣ�if����ֻҪcur�ļ��㲻ͬ�Ϳ�����Ŷ������len
		//���㲿�ֵ��ж�ѭ��
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
			else if (flag == 1 && len2 <= 0 && len1 > 0) { cur = temp1->nums + jinwei; temp1 = temp1->pre; len1--; }//len=0��flag1��flag2����
			else if (flag == 2 && len1 <= 0 && len2 > 0) { cur = temp2->nums + jinwei;	temp2 = temp2->pre; len2--; }//����Ͻ�дelse�Ϳ�����
			else { return result; }
			//���������ж�
			if (cur < 0) {
				jinwei = -1;
				cur = cur + 10000;
			}
			else { jinwei = 0;}
			//������������result
			addfirstDBnode_Llintline_longint(result, cur);
	}

}

//�˷����ҷ���ѽ,����һ��long��������int[8]���ԣ�long[4]���ԣ�ǰ������λת����long��������Ҳ��ת����long
//��Ȼ������������ݽṹ����λ�˷����������ԣ������Ҳ���д�ˣ��Ҿͼ�дд�ɡ�
//�˼ӳ˼���������ѭ��
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
	//��cur�Ľ�λ
	long cur;
	long jinwei=0;
	//����3�������ڼ����
	long num1[2];
	long num2[2];
	long result_jinwei=0;
	//long curr;
	long result_num[4] = {0,0,0,0};
	for (int i = 0; i < nums1->len; i++) {//��ʽ
		num1[0] = temp1->nums % 100;
		num1[1] = temp1->nums / 100;
		for (int j = 0; j < nums2->len; j++)//��ʽ
		{
			num2[0] = temp2->nums % 100;
			num2[1] = temp2->nums / 100;
			//�ⲿ�ֲ���ֱ��longlong���
			//���Ӳ�ѭ���ˣ�ֱ������ѽ��
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
			//���������ǳ˷��Ľ����ֻ��Ϊ�ӷ���һ���֡�
			addfirstDBnode_Llintline_longint(tempresult, cur);
			//���е�cur�����˻��ÿ�����jinwei��������
		}
		//����add������cur֮��
		addfirstDBnode_Llintline_longint(tempresult, jinwei);
		jinwei = 0;
		//���ӷ��Ĳ��ּ�Ȩ���������0�ڵ㣬���Ľڵ�����i���
		for (int k = 0; k < i; k++) {
			addlastDBnode_Llintline_longint(tempresult, 0);
		}
		//���ӷ�ע���������޷��żӷ������Բ�����ô�˴������ȥ�Ķ������ġ�
		tempresult = qushouzero(tempresult);
		result=unsightnumsadd(tempresult,result);
		clear_DBlist(tempresult);
		temp1 = temp1->pre;
		//temp2��Ҫ���ð�
		temp2= nums2->head->pre;
	}
	//���
	//ȷ������������
	result->head->nums = nums1->head->nums * nums2->head->nums;
	return result;
}

Llintline* numsadd(Llintline* nums1, Llintline* nums2) {
	Llintline* result;
	result = (Llintline*)malloc(sizeof(Llintline));
	//�����������������ź����֡�ͬ�żӣ���ż���ǰ������ǰ������ɶ�����øɣ���
	if (nums1->head->nums * nums2->head->nums > 0) { result = unsightnumsadd(nums1, nums2); }
	else{result = unsightnumsminus(nums1, nums2);}
	if (nums1->head->nums < 0) { result->head->nums = result->head->nums * (-1); }
	return result;
}

Llintline* numsminus(Llintline* nums1, Llintline* nums2) {
	Llintline* result;
	result = (Llintline*)malloc(sizeof(Llintline));
	//�����������������ź����֡�ͬ�ż�����żӡ�ǰ������ǰ������ɶ�����øɣ���
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
	//�ж���û����
	char f[2]="-+";
	if (a[0] == f[0]) { 
		line->head->nums = -1;  
		isfuhao = 1; }
	else if (a[0] == f[1]) { isfuhao = 1; }
	else { isfuhao = 0; }
	//ǿתlong
	//�ֳ������֣�4λ���ڵ㣬�Ͳ�����λ���ڵ�Ŀ�ͷ����
	//Ѱַ����Ȩѭ��������0��c֮�䣬��i�̳У�le-4*��i+1����le-i*4֮�䣬��j�̳У�temp��j�Ĺ�ϵ��temp��0����Ӧa��j-��le-4*��i+1������ȡ��
	//long=temp��0��*1000+������100������10.����
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
	//b�����ֲ��ֵĳ�������
	//ֱ��ת����a[isfuhao]��Ȩ1��a[isfuhao+1]��Ȩ10��ֱ��b
	if (b == 0) { return line; }
	else {
		for (int i = 0; i < b; i++) {
			temp[i] = (long)(a[isfuhao + i] - fuhao0[0]);
		}
		//��ÿλ����Ȩ���ӵ�һλ��Ȩ10��b-1-i�η���ʼ����i=b����
		//ԭ�ؼ�Ȩ�ķ��������Ժ������ѭ����������
		for (int i = 0; i < b; i++) {//b������
			for (int j = 0; j < b - i - 1; j++)//��i�����ּ�Ȩ10��b-i-1��
				temp[i] = temp[i] * 10;
			cur = cur + temp[i];
		}
		addfirstDBnode_Llintline_longint(line, cur);
		return line;
	}
}

//ǰ�գ��󿪰� 
Llintline* stringtonum_doubleindex(char* a, int star, int over) {
	if (star > over) { return NULL; }
	else if (star == over) { return NULL; }
	//��Ȼд��������ݽṹ�������Ȼ��ֻҪ��ȥǰ��ĳ��ȾͿ����ˣ�����string�Ĳ���
	char* aa;
	aa = (char*)malloc(sizeof(char)*(over-star));//����\0��û�������Ҫ��Ҫ+1.
	for (int i = 0; i < over - star; i++) {
		aa[i] = a[i + star];
	}
	return stringtonum(aa, over - star);
}

//ȥ��0Ӧ���ڳ˷�����������
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

