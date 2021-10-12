#pragma once
//因为比较简单，所以节点和栈一起做了
//反正都是双向的节点，我干脆节点也用DBnode吧
//额，不行啊，存的数据不一样，要是做的是任意类型就好了。
//引申一下，对于任意类型的同数据量的节点来说是一样的。
//只含一个“任意类型”的双向节点可以是int，long int等。会发现只要变量数量相同，节点类型相同。就可以用任意类型的同类型节点表示。
//C语言泛型不完善，我就自己再搞一个同类型的吧
//那节点的end去了吧，还是用DB。
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
//节点部分，定义节点的creat和change
Node* creatnode_null();
Node* creatnode_Llintline(Llintline* num);
void change_node_Llintline(Node* node,Llintline* line);

//stack部分
//漏了一个吧，栈的创建？空栈和非空栈的创建
stack* creatstack_null();
stack* creatstack_node(Node* head);
int	lengthof(stack* sta);
bool isempty_stack(stack* sta);
void push(stack* sta, Llintline* num);
Llintline* pop(stack* sta);
Llintline* look(stack* sta);

//计算函数
Llintline* cacul(char* str);
//指针的使用应该严谨才对，我现在会不会是在滥用？好担心改某一个值，把一堆东西改了。