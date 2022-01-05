//manacher�㷨
//����һ��ֻ��СдӢ���ַ�a,b,c,d...��ɵ��ַ��� S ,�� S������Ĵ��ĳ��� ,�ַ����ĳ���Ϊn

//����1��Ԥ����ԭ�ַ��� 
//�ȶ�ԭ�ַ�������Ԥ����Ԥ�����õ�һ���µ��ַ������������ǳ�ΪS��
//����2��R��C�ĳ�ʼֵΪ-1�������뾶����pArr
//�����е����������Сƫ�����Rʵ�������ұ߽�λ�õ���һλ
//����3����ʼ���±� i = 0ȥ�����ַ���S
//��֧1��i > R ��Ҳ����i��R�⣬��ʱû��ʲô������ڵķ�����ֱ�ӱ���ƥ�䣬��ʱ�ǵÿ���C��RҪ��Ҫ���¡�
//�ܽ�һ�£�Manacher�㷨�ľ������̾�����ƥ�� -> ͨ���ж�i��R�Ĺ�ϵ���в�ͬ�ķ�֧���� -> ��������ֱ�������������ַ���

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100000001

void ProStr();		// ����Ԥ����,��������ַ�������β�Լ��ո����# 
int ManaCher();		// ���������������� 

char str1[N];
char str2[N];

int main() {
	gets(str1);
	ProStr(str1);
	ManaCher(str2);
	return 0;
}

void ProStr(char str[]) {
	int i,j,n = strlen(str);
	for(i = 0,j = 0;i <= 2*n;i++) {
		if(i%2 == 0) str2[i] = '#';
		else {
			str2[i] = str[j];
			j++;
		}
	}
	printf("%s\n",str2);
}

int ManaCher(char str[]) {
	int i,k1,k2,R = 0,M;
	for(i = 0;i<=strlen(str);i++) {//���ַ�������һ��,��iΪ�е�,������Ѱ�һ����� 
		k1 = i;k2 = i;
		while(k1>1 && k2<strlen(str) && str[k1-1] == str[k2+1]) { //����Խ�� 
			k1--;
			k2++;
			R++;
			}
		M = M>R ? M:R;//���������� 
		R = 0;
	}
	if(M > 1) M += 1;
	printf("%d",M);
	return 0;
}
