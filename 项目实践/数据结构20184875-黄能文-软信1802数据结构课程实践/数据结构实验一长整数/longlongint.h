#pragma once
#include"DBnode.h"
#include<stdbool.h>
 struct Llintline
{
	int len;
	DBnode* head;
};
 typedef struct Llintline Llintline;
//����������ҪǮ������һ�����͵������డ����ɾ�Ĳ��Ƿ�ռ��������
//����
Llintline* creatLlintline();
//���س���
int len_list(Llintline* list);
//�Ƿ��
bool isempty(Llintline* list);
//������ɶ����գ���һ��
void clear_DBlist(Llintline* list);
//����ͷ��β������λ��
void addfirstDBnode_Llintline(Llintline* head);
void addfirstDBnode_Llintline_longint(Llintline* head,long num);
void addlastDBnode_Llintline(Llintline* head);
void addlastDBnode_Llintline_longint(Llintline* head,long num);
void addanyw(Llintline* head, int index,long int num);
//ɾ��ͷβ����λ��
void delfirstDBnode(Llintline* head);
//�ģ�ͷβ������λ��
void change(Llintline* head, int n, int num);
void changefirsthao(Llintline* line);
//�������ⲿ�־��������˫��ѭ���������ݽṹ��ʾ���ֵ�����֮���ˣ���Ȼ�ǼӼ����ͳ˷��������а�stringת����num
//�������java����tostring����������ݽṹ�ģ������ֻ�����Ӧ�õı�
void tonum(Llintline* head);
//Ϊ�˴��븴�ã���Ӧ����д�޷������ӷ��ͼ�����
Llintline* unsightnumsadd(Llintline* nums1, Llintline* nums2);
Llintline* unsightnumsminus(Llintline* nums1, Llintline* nums2);
//Ȼ���ǰ������ŵļӷ��ͼ�����
Llintline* numsadd(Llintline* nums1, Llintline* nums2);
Llintline* numsminus(Llintline* nums1, Llintline* nums2);
//���ڳ˷�����Ȼ�����жϱȽϼ򵥡�
Llintline* numsmult(Llintline* nums1, Llintline* nums2);
//Ҫת�����ַ����ַ�����
Llintline* stringtonum(char* a,int l);
//�鷳�ˣ�����һ����˭���������ݽṹǿ���ء���string���޶���star��over��ȡ���֡�
Llintline* stringtonum_doubleindex(char* a, int star,int over);
//�����ǽ����ڲ�����ʹ�õĺ���������ʹ�õ�ʱ��Ӧ�ð����沿��ע�͵��������װ���Ͻ�����ʵ����private��
Llintline* qushouzero(Llintline* line);