#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<string>
using namespace std;
struct rec{ int L, P, S; } a[110];
int n, m;
int f[110][16010], q[16010];

bool operator <(rec a, rec b) {
	return a.S < b.S;
}

int calc(int i, int k) {
	return f[i - 1][k] - a[i].P * k;
}

int main()  {
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &a[i].L, &a[i].P, &a[i].S);
	sort(a + 1, a + m + 1);
	for (int i = 1; i <= m; i++) {
		// 初始化单调队列
		int l = 1, r = 0;
		// 把最初的候选集合插入队列
		for (int k = max(0, a[i].S - a[i].L); k <= a[i].S - 1; k++) {
			// 插入新决策，维护队尾单调性
			while (l <= r && calc(i, q[r]) <= calc(i, k)) r--;
			q[++r] = k;
		}
		for (int j = 1; j <= n; j++) {
			// 不粉刷时的转移
			f[i][j] = max(f[i - 1][j], f[i][j - 1]);
			// 粉刷第k+1~j块木板时的转移
			if (j >= a[i].S) {
				// 排除队头不合法决策
				while (l <= r && q[l] < j - a[i].L) l++;
				// 队列非空时，取队头进行状态转移
				if (l <= r) f[i][j] = max(f[i][j], calc(i, q[l]) + a[i].P * j);
			}
		}
	}
	cout << f[m][n] << endl;
}