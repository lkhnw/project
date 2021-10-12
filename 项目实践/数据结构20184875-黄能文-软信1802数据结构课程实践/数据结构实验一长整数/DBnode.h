struct DBnod
{
	long int nums;
	struct DBnod* next;
	struct DBnod* pre;
};
typedef struct DBnod DBnode;
//这算容器类吗？这是一个存着指针和数字的容器。不提供对指针的额外操作

DBnode* creatDBnode_null();
//
DBnode* creatDBnode_longint(long int num);
void change_dbnode_int(DBnode* dbhead, int num);