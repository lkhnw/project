#pragma once
//��Ϊ�Ƚϼ򵥣����Խڵ��ջһ������
//��������˫��Ľڵ㣬�Ҹɴ�ڵ�Ҳ��DBnode��
//����а���������ݲ�һ����Ҫ���������������;ͺ��ˡ�
//����һ�£������������͵�ͬ�������Ľڵ���˵��һ���ġ�
//ֻ��һ�����������͡���˫��ڵ������int��long int�ȡ��ᷢ��ֻҪ����������ͬ���ڵ�������ͬ���Ϳ������������͵�ͬ���ͽڵ��ʾ��
//C���Է��Ͳ����ƣ��Ҿ��Լ��ٸ�һ��ͬ���͵İ�
//�ǽڵ��endȥ�˰ɣ�������DB��
#include "longlongint.h"
#include<stdio.h>

 struct Node
{
	Llintline* num;
	struct Node* pre;
	struct Node* next;
};
 typedef struct Node Node;

struct Stack {
	int length;
	struct Node* head;
};
typedef struct Stack stack;
//�ڵ㲿�֣�����ڵ��creat��change
Node* creatnode_null();
Node* creatnode_Llintline(Llintline* num);
void change_node_Llintline(Node* node,Llintline* line);

//stack����
//©��һ���ɣ�ջ�Ĵ�������ջ�ͷǿ�ջ�Ĵ���
stack* creatstack_null();
stack* creatstack_node(Node* head);
int	lengthof(stack* sta);
bool isempty_stack(stack* sta);
void push(stack* sta, Llintline* num);
Llintline* pop(stack* sta);
Llintline* look(stack* sta);

//���㺯��
Llintline* cacul(char* str);
//ָ���ʹ��Ӧ���Ͻ��Ŷԣ������ڻ᲻���������ã��õ��ĸ�ĳһ��ֵ����һ�Ѷ������ˡ�