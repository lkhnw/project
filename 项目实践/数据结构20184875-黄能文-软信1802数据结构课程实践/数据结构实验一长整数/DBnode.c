#include<stdio.h>
#include "DBnode.h"
DBnode* creatDBnode_null() {
	//一开头就是用的指针指向头结点
	//这是创建节点啊一个啥都没连的节点。
	DBnode* node;
	node = (DBnode*)__vcrt_malloc_normal(sizeof(DBnode));
	node->next = NULL;
	node->nums = NULL;
	node->pre = NULL;
	return node;
}

DBnode* creatDBnode_longint(long int num) {
	//一开头就是用的指针指向头结点
	//这是创建节点啊一个啥都没连的节点。
	DBnode* node;
	node = (DBnode*)__vcrt_malloc_normal(sizeof(DBnode));
	node->next = NULL;
	node->nums = num;
	node->pre = NULL;
	return node;
}

//港真，这个函数简单得像没用啊，不过为了功能上的区分，还是写一写。
void change_dbnode_int(DBnode* node,int num) {
	node->nums = num;
}