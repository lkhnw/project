#include<stdio.h>
#include "DBnode.h"
DBnode* creatDBnode_null() {
	//һ��ͷ�����õ�ָ��ָ��ͷ���
	//���Ǵ����ڵ㰡һ��ɶ��û���Ľڵ㡣
	DBnode* node;
	node = (DBnode*)__vcrt_malloc_normal(sizeof(DBnode));
	node->next = NULL;
	node->nums = NULL;
	node->pre = NULL;
	return node;
}

DBnode* creatDBnode_longint(long int num) {
	//һ��ͷ�����õ�ָ��ָ��ͷ���
	//���Ǵ����ڵ㰡һ��ɶ��û���Ľڵ㡣
	DBnode* node;
	node = (DBnode*)__vcrt_malloc_normal(sizeof(DBnode));
	node->next = NULL;
	node->nums = num;
	node->pre = NULL;
	return node;
}

//���棬��������򵥵���û�ð�������Ϊ�˹����ϵ����֣�����дһд��
void change_dbnode_int(DBnode* node,int num) {
	node->nums = num;
}