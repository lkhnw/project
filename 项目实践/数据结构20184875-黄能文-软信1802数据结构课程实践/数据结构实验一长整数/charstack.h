#pragma once
#include<stdio.h>
#include<stdbool.h>

struct charNode
{
	//2��ԭ����fuhao[0]�Լ�����λ���ˣ���Ȼ��-�������ڡ�-��
	char fuhao[1];
	struct charNode* pre;
	struct charNode* next;
};
typedef struct charNode charNode;

struct charStack {
	int length;
	charNode* head;
};
typedef struct charStack charstack;
//�ڵ㲿�֣�����ڵ��creat��change
charNode* creatcharnode_null();
charNode* creatcharnode_char(char a);
void change_charnode_char(charNode* charnode, char fuhao);

//stack����
//©��һ���ɣ�ջ�Ĵ�������ջ�ͷǿ�ջ�Ĵ���
charstack* creatcharstack_null();
charstack* creatcharstack_charnode(charNode* fuhaotou);
int	lengthofcharstack(charstack* sta);
bool isempty_charstack(charstack* sta);
void pushincharstack(charstack* sta, char fuhao);
char popofcharstack(charstack* sta);
char lookcharstack(charstack* sta);