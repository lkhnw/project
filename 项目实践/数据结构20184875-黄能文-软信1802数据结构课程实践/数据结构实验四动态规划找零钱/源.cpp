#include <stdio.h>
#include <malloc.h>
int buttom_up(int list[],int len,int n);
int main() {
	int nums[3], len, n,num;
	//�ļ�����
	FILE* fp;
	errno_t err = fopen_s(&fp, "input.txt", "r");
	if (err != 0) {
		printf("���ļ�ʧ��!\n");
		return 0;
	}
	else { printf("���ļ��ɹ�!\n"); }

	//��ȡ�ļ��������
	//��ȡ��һ�м����鳤��
	if (fscanf_s(fp, "%d", &len) != EOF) {
	}
	else { printf("��ȡ��һ������ʧ��"); }
	//��ȡ�ڶ���
	for (int i = 0; i < len; i++) {
		if (fscanf_s(fp, "%d", &num) != EOF) {
			nums[i] = num;
		}
		else { printf("��ȡ�ڶ�������ʧ��"); }
	}
	//��ȡ������
		if (fscanf_s(fp, "%d", &n) != EOF) {
		}else{printf("��ȡ������ʧ��"); }
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
		int temp = 10000;//������Ϊ�˷�ֹ����������int�������һ��
		for (int j = 0; j < len; j++) {
			//�����Ž�
			if (i - list[j] >= 0) {
				int k = i - list[j];//�����ӽṹ
				//���µ�ǰ���Ž�
				if (result[k] + 1 < temp) {
					temp = result[k] + 1;
				}
			}
		}
		//�������Ž�
		result[i] = temp;
	}
	return result[n];
}