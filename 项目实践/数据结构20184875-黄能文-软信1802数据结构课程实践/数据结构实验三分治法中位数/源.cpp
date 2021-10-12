#include<stdio.h>
#include <string.h>
int Findmid(int list1[],int list2[],int start,int end,int len);
int MIN = -2147483648;
int MAX = 2147483648;
int main(){
	//˼·����λ����ߵ������ұߵ�������һ����
	int numlist1[22] = { MIN }, numlist2[22] = {MIN}, n ,num;
	//�ļ�����
	FILE* fp;
	errno_t err = fopen_s(&fp,"input.txt", "r");
	if (err != 0) {
		printf("���ļ�ʧ��!\n");
		return 0;
	}
	else { printf("���ļ��ɹ�!\n"); }

	//��ȡ�ļ��������
	//��ȡ��һ�м����鳤��
	if (fscanf_s(fp, "%d", &num) != EOF) {
		//printf("%d\n", num);
		n = num;
	}
	else { printf("����"); }
	//��ȡ�ڶ��У�����һ������
	for (int i = 1; i <= n; i++) {
		if (fscanf_s(fp, "%d", &num) != EOF) {
			numlist1[i] = num;
		}
		else { printf("����"); }
	}
	//��ȡ�����У��ڶ�������
	for (int i = 1; i <= n; i++) {
		if (fscanf_s(fp, "%d", &num) != EOF) {
			numlist2[i] = num;
		}
		else { printf("����"); }
	}
	fclose(fp);
	//����ĵ�һ��������Сֵ����Ч�������һ���������ֵ������ݹ麯��
	numlist1[n + 1] = numlist2[n + 1] = MAX;

	fopen_s(&fp, "output.txt", "w");
	int result = Findmid(numlist1, numlist2, 1, n, n + 1);
	fprintf(fp,"%d",result);
	fclose(fp);
}

int Findmid(int list1[], int list2[], int start, int end,int len) {
	int mid = (start + end) / 2;
	if (list1[mid] > list2[len - mid + 1]) {
		return Findmid(list1, list2, start, mid, len);
	}
	else if (list1[mid] < list2[len - mid - 1]) {
		return Findmid(list1, list2, mid, end, len);
	}
	else {
		return (list1[mid] + list2[len - mid]) / 2;
	}
}