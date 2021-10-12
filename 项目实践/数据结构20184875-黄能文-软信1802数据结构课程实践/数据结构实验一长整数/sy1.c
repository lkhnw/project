/*
   写写文档
   (1)josehp换
      人按序列排
      序列对应的数代表密码
      对于密码，只有取出这个操作
      n个数，按照取第m个数（循环）
      直到，所有数都被取出
      利用顺序表单向循环链表。
      两种都用吗，好吧
    
   （2）这不是数据库行为嘛。
        b+树好用呐，为啥用线性表。
        主要看检索，但是检索也检索很多值
        还有排序，检索分类，排序，输出
        好像用链表好一点，能存多种数据。

    （4）长整数四则运算
        点名要求用循环双向链表
        
        那计算部分是重载运算符还是写函数？
        写函数吧
        链表栈，运算符栈，后缀运算符计算栈，嗯不需要其它结构体了
        提示了long int的范围，还说一个节点0-9999范围较好
        这提示简直不要太好
        今天老师也讲了用栈和队列
        现在开始吧！
        写一个栈，写一个队列，链表
        输入的时候是一个表达式啊。
        代码规划如下
        main函数
            输入string、char*
            对string检查（这是个循环），同时准备链表数据结构准备接受长整数，
                变后缀运算符算法：
                        准备两个栈存储长整型和运算符char
                        准备队列？直接string也可以吧，既然按顺序了，那直接计算也可以啊
                        那就直接计算吧
            输出最后的那个链表，注意逗号分隔四位哦。还有去0。
*/
#include<stdio.h>
#include "stack.h"
int main() {
    /*
    Llintline* result1 = creatLlintline();
    Llintline* result2 = creatLlintline();
    Llintline* result3 = creatLlintline();
    addfirstDBnode_Llintline_longint(result1, 5678);
    addfirstDBnode_Llintline_longint(result1, 0);
    addfirstDBnode_Llintline_longint(result2, 22);
    result3 = numsmult(result1, result2);
    tonum(result3);
    // */

    // tonum(stringtonum("29", 2));

   // /*
    char* str=(char*)__vcrt_malloc_normal(200*sizeof(char));
    Llintline* result=creatLlintline();
    printf("请输入计算表达式，以“#”结尾\n");
    scanf_s("%s", str,200);
    //中缀表达式化成后缀表达式计算？
    result = cacul(str);
    printf("计算结果是：");
    tonum(result);
   // */
}