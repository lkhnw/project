/*
   дд�ĵ�
   (1)josehp��
      �˰�������
      ���ж�Ӧ������������
      �������룬ֻ��ȡ���������
      n����������ȡ��m������ѭ����
      ֱ��������������ȡ��
      ����˳�����ѭ������
      ���ֶ����𣬺ð�
    
   ��2���ⲻ�����ݿ���Ϊ�
        b+�������ţ�Ϊɶ�����Ա�
        ��Ҫ�����������Ǽ���Ҳ�����ܶ�ֵ
        �������򣬼������࣬�������
        �����������һ�㣬�ܴ�������ݡ�

    ��4����������������
        ����Ҫ����ѭ��˫������
        
        �Ǽ��㲿�����������������д������
        д������
        ����ջ�������ջ����׺���������ջ���Ų���Ҫ�����ṹ����
        ��ʾ��long int�ķ�Χ����˵һ���ڵ�0-9999��Χ�Ϻ�
        ����ʾ��ֱ��Ҫ̫��
        ������ʦҲ������ջ�Ͷ���
        ���ڿ�ʼ�ɣ�
        дһ��ջ��дһ�����У�����
        �����ʱ����һ�����ʽ����
        ����滮����
        main����
            ����string��char*
            ��string��飨���Ǹ�ѭ������ͬʱ׼���������ݽṹ׼�����ܳ�������
                ���׺������㷨��
                        ׼������ջ�洢�����ͺ������char
                        ׼�����У�ֱ��stringҲ���԰ɣ���Ȼ��˳���ˣ���ֱ�Ӽ���Ҳ���԰�
                        �Ǿ�ֱ�Ӽ����
            ��������Ǹ�����ע�ⶺ�ŷָ���λŶ������ȥ0��
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
    printf("�����������ʽ���ԡ�#����β\n");
    scanf_s("%s", str,200);
    //��׺���ʽ���ɺ�׺���ʽ���㣿
    result = cacul(str);
    printf("�������ǣ�");
    tonum(result);
   // */
}