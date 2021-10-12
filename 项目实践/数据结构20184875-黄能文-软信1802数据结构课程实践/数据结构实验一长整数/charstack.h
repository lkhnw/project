#pragma once
#include<stdio.h>
#include<stdbool.h>

struct charNode
{
	//2的原因是fuhao[0]自己矫正位长了，不然“-”不等于“-”
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
//节点部分，定义节点的creat和change
charNode* creatcharnode_null();
charNode* creatcharnode_char(char a);
void change_charnode_char(charNode* charnode, char fuhao);

//stack部分
//漏了一个吧，栈的创建？空栈和非空栈的创建
charstack* creatcharstack_null();
charstack* creatcharstack_charnode(charNode* fuhaotou);
int	lengthofcharstack(charstack* sta);
bool isempty_charstack(charstack* sta);
void pushincharstack(charstack* sta, char fuhao);
char popofcharstack(charstack* sta);
char lookcharstack(charstack* sta);