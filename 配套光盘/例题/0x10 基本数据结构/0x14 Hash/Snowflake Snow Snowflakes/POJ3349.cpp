#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
const int SIZE = 100010;
int n, tot, P = 99991;
int snow[SIZE][6], head[SIZE], next[SIZE];

int H(int *a) {
	int sum = 0, mul = 1;
	for (int i = 0; i < 6; i++) {
		sum = (sum + a[i]) % P;
		mul = (long long)mul * a[i] % P;
	}
	return (sum + mul) % P;
}

bool equal(int *a, int *b) {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++) {
			bool eq = 1;
			for (int k = 0; k < 6; k++)
				if (a[(i+k)%6] != b[(j+k)%6]) eq = 0;
			if (eq) return 1; 
			eq = 1;
			for (int k = 0; k < 6; k++)
				if (a[(i+k)%6] != b[(j-k+6)%6]) eq = 0;
			if (eq) return 1;
		}
	return 0;
}

bool insert(int *a) {
	int val = H(a);
	// 遍历表头head[val]指向的链表，寻找形状相同的雪花 
	for (int i = head[val]; i; i = next[i]) {
		if (equal(snow[i], a)) return 1;
	}
	// 未找到形状相同的雪花，执行插入 
	++tot;
	memcpy(snow[tot], a, 6 * sizeof(int));
	next[tot] = head[val];
	head[val] = tot;
	return 0;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int a[10];
		for (int j = 0; j < 6; j++) scanf("%d", &a[j]);
		if (insert(a)) {
			puts("Twin snowflakes found.");
			return 0;
		}
	}
	puts("No two snowflakes are alike.");
}