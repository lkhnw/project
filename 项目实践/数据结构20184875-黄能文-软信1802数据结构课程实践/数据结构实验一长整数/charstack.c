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

//ջ����
charstack* creatcharstack_null() {
	charstack* sta;
	sta = (charstack*)malloc(sizeof(charstack));
	sta->head = creatcharnode_null();
	sta->length = 0;
	return sta;
}
//ջ֮��Ľڵ㿽���е��Ѹ㣬����ֻ�ṩ������ջ�����ṩ�����ڵ㣬ֻ��head��num������ڵ㿽����Ȼ��ѽڵ�����ɾ�ˣ�����ԭ���Ľڵ��ˡ��ɼ�ûɶ�á�
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
//����Ԫ��
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

//ȡ��Ԫ��
char popofcharstack(charstack* sta) {
	if (sta->length == 0) { return NULL; }
	//Ҫ�쳣���˰�
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
