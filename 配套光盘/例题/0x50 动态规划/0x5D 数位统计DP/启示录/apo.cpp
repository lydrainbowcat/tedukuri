#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long f[21][4];
int t, n, m;

void prework() {
	f[0][0] = 1;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 3; j++) {
			f[i + 1][j + 1] += f[i][j];
			f[i + 1][0] += f[i][j] * 9;
		}
		f[i + 1][3] += f[i][3] * 10;
	}
}

int main() {
	prework();
	cin >> t; // 数据组数
	while (t--) {
		scanf("%d", &n); // 题目中的X
		// 第n个魔鬼数有m位
		for (m = 3; f[m][3] < n; m++);
		// 试填第i位，末尾已有k个6（k=3也表示已经是魔鬼数）
		for (int i = m, k = 0; i; i--) {
			// 从小到大枚举第i位填的数字j
			for (int j = 0; j <= 9; j++) {
				// 求出后边的i-1位有多少种填法能让整个数是魔鬼数
				long long cnt = f[i - 1][3];
				if (j == 6 || k == 3)
					for (int l = max(3 - k - (j == 6), 0); l<3; l++)
						cnt += f[i - 1][l];
				// 如果cnt比n小，说明第n个魔鬼数的第i位应该比j更大
				if (cnt < n) {
					n -= cnt;
				}
				// 否则，第i位就应该是j
				else {
					if (k < 3) {
						if (j == 6) k++; else k = 0;
					}
					printf("%d", j);
					break;
				}
			}
		}
		cout << endl;
	}
}
