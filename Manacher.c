//manacher算法
//给出一个只由小写英文字符a,b,c,d...组成的字符串 S ,求 S中最长回文串的长度 ,字符串的长度为n

//步骤1：预处理原字符串 
//先对原字符串进行预处理，预处理后得到一个新的字符串，这里我们称为S，
//步骤2：R和C的初始值为-1，创建半径数组pArr
//这里有点与概念相差的小偏差，就是R实际是最右边界位置的右一位
//步骤3：开始从下标 i = 0去遍历字符串S
//分支1：i > R ，也就是i在R外，此时没有什么花里胡哨的方法，直接暴力匹配，此时记得看看C和R要不要更新。
//总结一下，Manacher算法的具体流程就是先匹配 -> 通过判断i与R的关系进行不同的分支操作 -> 继续遍历直到遍历完整个字符串

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100000001

void ProStr();		// 数组预处理,给输入的字符串的首尾以及空格加入# 
int ManaCher();		// 计算最大回文数长度 

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
	for(i = 0;i<=strlen(str);i++) {//将字符串遍历一遍,以i为中点,向两边寻找回文数 
		k1 = i;k2 = i;
		while(k1>1 && k2<strlen(str) && str[k1-1] == str[k2+1]) { //避免越界 
			k1--;
			k2++;
			R++;
			}
		M = M>R ? M:R;//回文数长度 
		R = 0;
	}
	if(M > 1) M += 1;
	printf("%d",M);
	return 0;
}
