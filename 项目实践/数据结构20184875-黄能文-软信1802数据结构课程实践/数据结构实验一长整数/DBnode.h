struct DBnod
{
	long int nums;
	struct DBnod* next;
	struct DBnod* pre;
};
typedef struct DBnod DBnode;
//����������������һ������ָ������ֵ����������ṩ��ָ��Ķ������

DBnode* creatDBnode_null();
//
DBnode* creatDBnode_longint(long int num);
void change_dbnode_int(DBnode* dbhead, int num);