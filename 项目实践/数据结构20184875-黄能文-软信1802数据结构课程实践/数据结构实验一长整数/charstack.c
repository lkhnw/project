#pragma once
#include "charstack.h"
charNode* creatcharnode_null() {
	charNode* node;
	node = (charNode*)malloc(sizeof(charNode));
	node->pre = NULL;
	node->next = NULL;
	node->fuhao[0] = NULL;
	return node;
}

charNode* creatcharnode_char(char a) {
	charNode* node;
	node = (charNode*)malloc(sizeof(charNode));
	node->pre = NULL;
	node->next = NULL;
	node->fuhao[0] = a;
	return node;
}

void change_charnode_char(charNode* node, char fuhao) {
	node->fuhao[0] = fuhao;
}

//栈部分
charstack* creatcharstack_null() {
	charstack* sta;
	sta = (charstack*)malloc(sizeof(charstack));
	sta->head = creatcharnode_null();
	sta->length = 0;
	return sta;
}
//栈之间的节点拷贝有点难搞，我这只提供创造新栈，不提供拷贝节点，只有head的num深拷贝，节点拷贝，然后把节点上下删了，报废原本的节点了。可见没啥用。
charstack* creatcharstack_charnode(charNode* head) {
	charstack* sta;
	sta = (charstack*)malloc(sizeof(charstack));
	sta->head = head;
	sta->head->next = NULL;
	sta->head->pre = NULL;
	return sta;
}

int lengthofcharstack(charstack* sta) {
	return sta->length;
}

bool isempty_charstack(charstack* sta) {
	return sta->length == 0;
}
//增加元素
void pushincharstack(charstack* sta, char fuhao) {
	charNode* n;
	n = (charNode*)malloc(sizeof(charNode));
	n->fuhao[0] = fuhao;
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
char popofcharstack(charstack* sta) {
	if (sta->length == 0) { return NULL; }
	//要异常吗不了吧
	else {
		char fuhao[2];
		fuhao[0] = sta->head->pre->fuhao[0];
		sta->head->pre = sta->head->pre->pre;
		sta->head->pre->next->pre = NULL;
		sta->head->pre->next->next = NULL;
		sta->head->pre->next = sta->head;
		sta->length--;
		return fuhao[0];
	}
}

char lookcharstack(charstack* sta) {
	if (sta->length == 0) { return NULL; }
	else { return sta->head->pre->fuhao[0]; }
}
