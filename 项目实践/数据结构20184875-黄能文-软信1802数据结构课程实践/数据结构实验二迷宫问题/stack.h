#include<stdio.h>
#include<stdbool.h>

struct twoint_Node
{
	//2的原因是fuhao[0]自己矫正位长了，不然“-”不等于“-”
	int z[2];
	struct twoint_Node* pre;
	struct twoint_Node* next;
};
typedef struct twoint_Node twoint_node;

struct twoint_Stack {
	int length;
	twoint_node* head;
};
typedef struct twoint_Stack twoint_stack;
//节点部分，定义节点的creat和change
twoint_node* creat_twoint_node_null();
twoint_node* creat_twoint_node_twoint(int x,int y);
void change_twoint_node_twoint(twoint_node* node,int x,int y);

//stack部分
//漏了一个吧，栈的创建？空栈和非空栈的创建
twoint_stack* creat_twoint_stack_null();
twoint_stack* creat_twoint_stack_twoint_node(twoint_node* head);
int	lengthof_twoint_stack(twoint_stack* sta);
bool isempty_twoint_stack(twoint_stack* sta);
void pushin_twoint_stack(twoint_stack* sta,int x,int y);
int* popof_twoint_stack(twoint_stack* sta);
int* look_twoint_stack(twoint_stack* sta);

qiujie(int a[][8], int x, int y, int** start, int** over);
toString(twoint_stack* sta);