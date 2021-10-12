#include <stdio.h>
#include <malloc.h>
int buttom_up(int list[],int len,int n);
int main() {
	int nums[3], len, n,num;
	//文件操作
	FILE* fp;
	errno_t err = fopen_s(&fp, "input.txt", "r");
	if (err != 0) {
		printf("打开文件失败!\n");
		return 0;
	}
	else { printf("打开文件成功!\n"); }

	//读取文件里的数字
	//读取第一行即数组长度
	if (fscanf_s(fp, "%d", &len) != EOF) {
	}
	else { printf("读取第一个数字失败"); }
	//读取第二行
	for (int i = 0; i < len; i++) {
		if (fscanf_s(fp, "%d", &num) != EOF) {
			nums[i] = num;
		}
		else { printf("读取第二行数字失败"); }
	}
	//读取第三行
		if (fscanf_s(fp, "%d", &n) != EOF) {
		}else{printf("读取第三行失败"); }
	fclose(fp);


	fopen_s(&fp, "output.txt", "w");
	int result = buttom_up(nums,len,n);
	fprintf(fp, "%d", result);
	fclose(fp);
}

int buttom_up(int list[],int len, int n) {
	int* result = (int*)malloc(sizeof(int) * n + 1) ;
	result[0] = 0;
	for (int i = 1; i <= n; i++) {
		int temp = 10000;//正无穷为了防止溢出，最好是int最大数减一。
		for (int j = 0; j < len; j++) {
			//得最优解
			if (i - list[j] >= 0) {
				int k = i - list[j];//最优子结构
				//更新当前最优解
				if (result[k] + 1 < temp) {
					temp = result[k] + 1;
				}
			}
		}
		//最终最优解
		result[i] = temp;
	}
	return result[n];
}