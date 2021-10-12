#include "stack.h"
twoint_node* creat_twoint_node_null() {
	twoint_node* node;
	node = (twoint_node*)malloc(sizeof(twoint_node));
	node->pre = NULL;
	node->next = NULL;
	node->z[0] = NULL;
	node->z[1] = NULL;
	return node;
}

twoint_node* creat_twoint_node_twoint(int x,int y) {
	twoint_node* node;
	node = (twoint_node*)malloc(sizeof(twoint_node));
	node->pre = NULL;
	node->next = NULL;
	node->z[0] = x;
	node->z[1] = y;
	return node;
}

void change_twoint_node_twoint(twoint_node* node,int x,int y) {
	node->z[0] = x;
	node->z[1] = y;
}

//ջ����
twoint_stack* creat_twoint_stack_null() {
	twoint_stack* sta;
	sta = (twoint_stack*)malloc(sizeof(twoint_stack));
	sta->head = creat_twoint_node_null();
	sta->length = 0;
	return sta;
}
//ջ֮��Ľڵ㿽���е��Ѹ㣬����ֻ�ṩ������ջ�����ṩ�����ڵ㣬ֻ��head��num������ڵ㿽����Ȼ��ѽڵ�����ɾ�ˣ�����ԭ���Ľڵ��ˡ��ɼ�ûɶ�á�
twoint_stack* creat_twoint_stack_twoint_node(twoint_node* head) {
	twoint_stack* sta;
	sta = (twoint_stack*)malloc(sizeof(twoint_stack));
	sta->head = head;
	sta->head->next = NULL;
	sta->head->pre = NULL;
	return sta;
}

int lengthof_twoint_stack(twoint_stack* sta) {
	return sta->length;
}

bool isempty_twoint_stack(twoint_stack* sta) {
	return sta->length == 0;
}
//����Ԫ��
void pushin_twoint_stack(twoint_stack* sta,int x,int y) {
	twoint_node* n;
	n = (twoint_node*)malloc(sizeof(twoint_node));
	n->z[0] = x;
	n->z[1] = y;
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
int* popof_twoint_stack(twoint_stack* sta) {
	if (sta->length == 0) { return NULL; }
	//Ҫ�쳣���˰�
	else {
		int z[2];
		*z = sta->head->pre->z;
		sta->head->pre = sta->head->pre->pre;
		sta->head->pre->next->pre = NULL;
		sta->head->pre->next->next = NULL;
		sta->head->pre->next = sta->head;
		sta->length--;
		return z;
	}
}

int* look_twoint_stack(twoint_stack* sta) {
	if (sta->length == 0) { return NULL; }
	else { return sta->head->pre->z; }
}

toString(twoint_stack* sta) {
	if (sta->length == 0) { printf("�޽�"); }
	else {
		printf("��Ϊ:\n");
		printf("(x,y)\n");
		twoint_node* node = sta->head->next;
		while (node != sta->head) {
			//x��y��z˳�򷴹���
			printf("(%d,%d)", node->z[1], node->z[0]);
			node = node->next;
		}
	}
}

qiujie(int a[][8],int x,int y,int* start,int* over) {
	twoint_stack* stack = creat_twoint_stack_null();
	int temp[2];
	temp[0] = start[0];//
	temp[1] = start[1];
	pushin_twoint_stack(stack,start[0],start[1]);
	a[0][0] = 1;
	while (true) {
		//����
		if (temp[0] > 0 && a[temp[0] - 1][temp[1]] != 1) {
			temp[0]--;
			pushin_twoint_stack(stack, temp[0], temp[1]);
			a[temp[0]][temp[1]] = 1;
			printf("��");
		}
		else if (temp[1] < x-1 && a[temp[0]][temp[1]+1] != 1) {
			temp[1]++;
			pushin_twoint_stack(stack, temp[0], temp[1]);
			a[temp[0]][temp[1]] = 1;
			printf("��");
		}
		else if(temp[0]<y-1 && a[temp[0]+1][temp[1]] != 1){
			temp[0]++;
			pushin_twoint_stack(stack, temp[0], temp[1]);
			a[temp[0]][temp[1]] = 1;
			printf("��");
		}
		else if (temp[1] > 0 && a[temp[0]][temp[1] - 1] != 1) {
			temp[1]--;
			pushin_twoint_stack(stack, temp[0], temp[1]);
			a[temp[0]][temp[1]] = 1;
			printf("��");
		}
		else {
			temp[0] = look_twoint_stack(stack)[0];
			temp[1] = look_twoint_stack(stack)[1];
				popof_twoint_stack(stack);
		}
		if (stack->length == 0 || (look_twoint_stack(stack)[0] == over[0] && look_twoint_stack(stack)[1] == over[1])) {
				toString(stack); break;
		}
	}
}