#include<stdio.h>
#include <string.h>
int Findmid(int list1[],int list2[],int start,int end,int len);
int MIN = -2147483648;
int MAX = 2147483648;
int main(){
	//思路：中位数左边的数和右边的数个数一样多
	int numlist1[22] = { MIN }, numlist2[22] = {MIN}, n ,num;
	//文件操作
	FILE* fp;
	errno_t err = fopen_s(&fp,"input.txt", "r");
	if (err != 0) {
		printf("打开文件失败!\n");
		return 0;
	}
	else { printf("打开文件成功!\n"); }

	//读取文件里的数字
	//读取第一行即数组长度
	if (fscanf_s(fp, "%d", &num) != EOF) {
		//printf("%d\n", num);
		n = num;
	}
	else { printf("错误"); }
	//读取第二行，即第一个数组
	for (int i = 1; i <= n; i++) {
		if (fscanf_s(fp, "%d", &num) != EOF) {
			numlist1[i] = num;
		}
		else { printf("错误"); }
	}
	//读取第三行，第二个数组
	for (int i = 1; i <= n; i++) {
		if (fscanf_s(fp, "%d", &num) != EOF) {
			numlist2[i] = num;
		}
		else { printf("错误"); }
	}
	fclose(fp);
	//数组的第一个赋予最小值，有效数字最后一个赋予最大值，方便递归函数
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