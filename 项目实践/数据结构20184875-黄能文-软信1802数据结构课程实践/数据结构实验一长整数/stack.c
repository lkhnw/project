#include<stdio.h>
#include<stdbool.h>
//׼��������дջ
#include "stack.h"
#include"charstack.h"
//˫������ջ��һ��βָ�롣�����е��˷ѿռ�
Node* creatnode_null() {
	Node* node;
	node = (Node*)malloc(sizeof(Node));
	node->pre = NULL;
	node->next = NULL;
	node->num = NULL;
	return node;
}

Node* creatnode_Llintline( Llintline* a) {
	Node* node;
	node = (Node*)malloc(sizeof(Node));
	node->pre = NULL;
	node->next = NULL;
	node->num = a;
	return node;
}

void change_node_Llintline(Node* node, Llintline* line) {
	node->num = line;
}

//ջ����
stack* creatstack_null() {
	stack* sta;
	sta = (stack*)malloc(sizeof(stack));
	sta->head = creatnode_null();
	sta->length = 0;
	return sta;
}
//ջ֮��Ľڵ㿽���е��Ѹ㣬����ֻ�ṩ������ջ�����ṩ�����ڵ㣬ֻ��head��num������ڵ㿽����Ȼ��ѽڵ�����ɾ�ˣ�����ԭ���Ľڵ��ˡ��ɼ�ûɶ�á�
//����û�У�ͷ���û�á�
stack* creatstack_node(Node* head) {
	stack* sta;
	sta = (stack*)malloc(sizeof(stack));
	sta->head = head;
	sta->head->next = NULL;
	sta->head->pre = NULL;
	return sta;
}

int lengthof(stack* sta) {
	return sta->length;
}

bool isempty_stack(stack* sta) {
	return sta->length == 0;
}
//����Ԫ��
void push(stack* sta,Llintline* num){
	Node* n;
	n = (Node*)malloc(sizeof(Node));
	n->num = num;
	if (sta->length == 0) {
		sta->head->next = n;
		sta->head->pre = n;
		n->next = sta->head;
		n->pre = sta->head;
	}
	else {
		n->next = sta->head;
		sta->head->pre->next = n;
		n->pre = sta->head->pre;
		sta->head->pre = n;
	}
	sta->length++;
}

//ȡ��Ԫ��
Llintline* pop(stack* sta) {
	if (sta->length == 0) { return NULL; }
	//Ҫ�쳣���˰�
	else {
		Llintline* num;
		num = (Llintline*)malloc(sizeof(Llintline));
		num = sta->head->pre->num;
		sta->head->pre = sta->head->pre->pre;
		sta->head->pre->next->pre = NULL;
		sta->head->pre->next->next = NULL;
		sta->head->pre->next = sta->head;
		sta->length--;
		return num;
	}
}

Llintline* look(stack* sta){
	if (sta->length == 0) { return NULL; }
	else { return sta->head->pre->num; }
}

Llintline* cacul(char* str) {
	//˫ָ���ж�
	//����һ��˼·��
	//˫ָ���飬���ȵ����ֿ������ֺ���������Լ����š��������ź����һ���Ǹ��ţ���һ���͸��ŵĿ϶�Ҳ�Ǹ��š�
	//��ָ�룺�������֣���һ�����������ⲻ�����ַ���
	//��ָ��:����һ��ת��������
	//�ж��ַ�������ջ��ջ
	//����ָ���������ַ���һ��
	stack* sta=creatstack_null();
	charstack* charsta = creatcharstack_null();
	char fuhaoji[9] = "+-*/()#09";
	long i = 0, j = 0;
	while (true) {
		if (str[i] >= fuhaoji[7] && str[i] <= fuhaoji[8]) {//�ж�Ϊ������ɶ�����øɰ�
		}
		else {
			//������Ƿ�������,�Ȱ�ǰ������ֽ�һ�£�������������������ջ��
			//��һλ��ʱ���������ý�
			//�����ź�����ķ���һ���ý�������0���������ź����Ҳ�ý�����0���������������
			if (i != j) {
				push(sta, stringtonum_doubleindex(str, j, i));
			}
			//Ȼ������ָ��λ��
			j = i+1;
			//������ջ�꣬�ַ���ջ���ַ������ȼ���ǰ��һ���ߵ��������ջ��
			//д��ô��ifЧ��Ҳ���߰����ñȽϰ����ȼ���������ĸ߾���ջ
			if(charsta->length==0 || youxianji( lookcharstack(charsta) < youxianji(str[i]) || str[i] == fuhaoji[4])){//�ܿ�ջ��+��-��*��/����
				pushincharstack(charsta, str[i]);
				if(str[i]==fuhaoji[4] && (str[i+1]==fuhaoji[1] || str[i+1]==fuhaoji[0])){
					push(sta, stringtonum("0",0,1));
				}
			}
			else if(str[i]==fuhaoji[6]){//�����ˣ���һ�����ˣ���#
				//��ջ��ֱ����
				while ( false == isempty_charstack(charsta)) {
					char ttt = popofcharstack(charsta);
					if (ttt == fuhaoji[0]) { push(sta, numsadd(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[1]) { push(sta, numsminus(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[2]) { push(sta, numsmult(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[3]) {}
					else if (ttt == fuhaoji[4]) {}
				}
				return pop(sta);
			}
			else if(str[i]==fuhaoji[5]){//�� ),���Ե������ȼ���ߵģ�,���ղ���ջ
				while (youxianji(lookcharstack(charsta)) >= youxianji(str[i]) ||lookcharstack==fuhaoji[4]) {
					char ttt = popofcharstack(charsta);
					if (ttt == fuhaoji[0]) { push(sta, numsadd(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[1]) { push(sta, numsminus(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[2]) { push(sta, numsmult(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[3]) {}
					else if (ttt == fuhaoji[4]) { break; }
				}

			}
			else {//��ջ�ˣ������ǻ��ɺ�׺���ʽ���������ˡ���һ������ջ����˳�Ҳ��һ��
				//��ջ�����ȼ��ȡ�i�����ȼ���ʱ��ֹͣ
				//��ջ�������Ų��ù�
				//ջ��ֻ����ǰ��5�ַ���
				//���꣬��ջ
				//��ջ������
				while (youxianji( lookcharstack(charsta))>=youxianji( str[i]) && false == isempty_charstack(charsta)) {
					char ttt = popofcharstack(charsta);
					if (ttt == fuhaoji[0]) { push(sta,numsadd(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[1]) { push(sta, numsminus(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[2]) { push(sta, numsmult(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[3]) {}
					else if (ttt == fuhaoji[4]){}
				}
				pushincharstack(charsta,str[i]);
			}

		}
		i++;
		
	}
}
//���ȼ�����
int youxianji(char fu) {
	char a[7] = "+-*/()";
	//������ջǰ���ȼ���ߣ���ջ�����ȼ����
	//�����ȼ���ߣ�����ִ����ʵ���Է��ھ��廷���￴��
	//������ջ����
	if (fu == a[0] || fu == a[1]) { return 1; }
	if (fu == a[2] || fu == a[3]) { return 2; }
	if (fu == a[5] || fu == a[4]) { return 0; }
}