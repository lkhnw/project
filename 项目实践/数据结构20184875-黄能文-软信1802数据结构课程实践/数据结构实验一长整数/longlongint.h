#pragma once
#include"DBnode.h"
#include<stdbool.h>
 struct Llintline
{
	int len;
	DBnode* head;
};
 typedef struct Llintline Llintline;
//反正声明不要钱，这是一个典型的容器类啊，增删改查是否空加输出走起
//构造
Llintline* creatLlintline();
//返回长度
int len_list(Llintline* list);
//是否空
bool isempty(Llintline* list);
//刚听到啥，清空？来一个
void clear_DBlist(Llintline* list);
//增，头，尾，任意位置
void addfirstDBnode_Llintline(Llintline* head);
void addfirstDBnode_Llintline_longint(Llintline* head,long num);
void addlastDBnode_Llintline(Llintline* head);
void addlastDBnode_Llintline_longint(Llintline* head,long num);
void addanyw(Llintline* head, int index,long int num);
//删，头尾任意位置
void delfirstDBnode(Llintline* head);
//改，头尾，任意位置
void change(Llintline* head, int n, int num);
void changefirsthao(Llintline* line);
//接下来这部分就是我这个双向循环链表数据结构表示数字的特殊之处了，当然是加减法和乘法啊，还有把string转化成num
//输出本来java里是tostring输出整个数据结构的，我这就只是输出应该的表达。
void tonum(Llintline* head);
//为了代码复用，我应该先写无符号数加法和减法。
Llintline* unsightnumsadd(Llintline* nums1, Llintline* nums2);
Llintline* unsightnumsminus(Llintline* nums1, Llintline* nums2);
//然后是包含符号的加法和减法，
Llintline* numsadd(Llintline* nums1, Llintline* nums2);
Llintline* numsminus(Llintline* nums1, Llintline* nums2);
//至于乘法，显然符号判断比较简单。
Llintline* numsmult(Llintline* nums1, Llintline* nums2);
//要转化的字符和字符长度
Llintline* stringtonum(char* a,int l);
//麻烦了，再做一个，谁叫你这数据结构强大呢。从string中限定的star和over截取数字。
Llintline* stringtonum_doubleindex(char* a, int star,int over);
//下面是仅供内部函数使用的函数。具体使用的时候，应该把下面部分注释掉，以免封装不严谨，其实就是private。
Llintline* qushouzero(Llintline* line);