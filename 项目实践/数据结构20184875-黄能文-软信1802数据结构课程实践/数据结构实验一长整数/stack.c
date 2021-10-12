#include<stdio.h>
#include<stdbool.h>
//准备用链表写栈
#include "stack.h"
#include"charstack.h"
//双向链表栈多一个尾指针。好像有点浪费空间
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

//栈部分
stack* creatstack_null() {
	stack* sta;
	sta = (stack*)malloc(sizeof(stack));
	sta->head = creatnode_null();
	sta->length = 0;
	return sta;
}
//栈之间的节点拷贝有点难搞，我这只提供创造新栈，不提供拷贝节点，只有head的num深拷贝，节点拷贝，然后把节点上下删了，报废原本的节点了。可见没啥用。
//软用没有，头结点没用。
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
//增加元素
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

//取出元素
Llintline* pop(stack* sta) {
	if (sta->length == 0) { return NULL; }
	//要异常吗不了吧
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
	//双指针判断
	//再理一遍思路，
	//双指针检查，首先得区分开来数字和运算符，以及负号。跟在括号后面的一定是负号，第一个就负号的肯定也是负号。
	//快指针：这是数字，下一个。。。。这不是数字返回
	//慢指针:将这一段转化成数字
	//判断字符，该入栈入栈
	//快慢指针设置在字符下一格。
	stack* sta=creatstack_null();
	charstack* charsta = creatcharstack_null();
	char fuhaoji[9] = "+-*/()#09";
	long i = 0, j = 0;
	while (true) {
		if (str[i] >= fuhaoji[7] && str[i] <= fuhaoji[8]) {//判断为数字了啥都不用干吧
		}
		else {
			//这里就是非数字区,先把前面的数字结一下，遇到数字是无条件入栈的
			//仅一位的时候，左括号让进
			//右括号后面跟的符号一定让进（不补0），左括号后面的也让进（补0）如果还是括号呢
			if (i != j) {
				push(sta, stringtonum_doubleindex(str, j, i));
			}
			//然后重设指针位置
			j = i+1;
			//数字入栈完，字符入栈，字符在优先级比前面一个高的情况下入栈。
			//写这么多if效率也不高啊，用比较吧优先级不比里面的高就入栈
			if(charsta->length==0 || youxianji( lookcharstack(charsta) < youxianji(str[i]) || str[i] == fuhaoji[4])){//管空栈，+，-，*，/，（
				pushincharstack(charsta, str[i]);
				if(str[i]==fuhaoji[4] && (str[i+1]==fuhaoji[1] || str[i+1]==fuhaoji[0])){
					push(sta, stringtonum("0",0,1));
				}
			}
			else if(str[i]==fuhaoji[6]){//结束了，算一波走人，管#
				//弹栈，直到空
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
			else if(str[i]==fuhaoji[5]){//管 ),可以弹出优先级最高的（,最终不入栈
				while (youxianji(lookcharstack(charsta)) >= youxianji(str[i]) ||lookcharstack==fuhaoji[4]) {
					char ttt = popofcharstack(charsta);
					if (ttt == fuhaoji[0]) { push(sta, numsadd(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[1]) { push(sta, numsminus(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[2]) { push(sta, numsmult(pop(sta), pop(sta))); }
					else if (ttt == fuhaoji[3]) {}
					else if (ttt == fuhaoji[4]) { break; }
				}

			}
			else {//出栈了，本来是换成后缀表达式。可以算了。）一定不进栈，与乘除也不一样
				//当栈内优先级比【i】优先级低时候停止
				//出栈符左括号不用管
				//栈里只能有前面5种符号
				//弹完，入栈
				//空栈不弹。
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
//优先级函数
int youxianji(char fu) {
	char a[7] = "+-*/()";
	//（在入栈前优先级最高，入栈后优先级最低
	//）优先级最高，立马执行其实可以放在具体环境里看。
	//）不进栈啊。
	if (fu == a[0] || fu == a[1]) { return 1; }
	if (fu == a[2] || fu == a[3]) { return 2; }
	if (fu == a[5] || fu == a[4]) { return 0; }
}