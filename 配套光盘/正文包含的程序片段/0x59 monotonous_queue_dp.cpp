// 单调队列优化多重背包
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<string>
using namespace std;
int n, m, V[210], W[210], C[210];
int f[20010], q[20010];

int calc(int i, int u, int k) {
	return f[u + k*V[i]] - k*W[i];
}

int main() {
	cin >> n >> m;
	memset(f, 0xcf, sizeof(f)); // -INF
	f[0] = 0;
	// 物品种类
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &V[i], &W[i], &C[i]);
		// 除以V[i]的余数
		for (int u = 0; u < V[i]; u++) {
			// 建立单调队列
			int l = 1, r = 0;
			// 把最初的候选集合插入队列
			int maxp = (m - u) / V[i];
			for (int k = maxp - 1; k >= max(maxp - C[i], 0); k--) {
				while (l <= r && calc(i, u, q[r]) <= calc(i, u, k)) r--;
				q[++r] = k;
			}
			// 倒序循环每个状态
			for (int p = maxp; p >= 0; p--) {
				// 排除过时决策
				while (l <= r && q[l] > p - 1) l++;
				// 取队头进行状态转移
				if (l <= r)
					f[u + p*V[i]] = max(f[u + p*V[i]], calc(i, u, q[l]) + p*W[i]);
				// 插入新决策，同时维护队尾单调性
				if (p - C[i] - 1 >= 0) {
					while (l <= r && calc(i, u, q[r]) <= calc(i, u, p - C[i] - 1)) r--;
					q[++r] = p - C[i] - 1;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) ans = max(ans, f[i]);
	cout << ans << endl;
}