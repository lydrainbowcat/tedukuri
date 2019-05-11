//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 156, M = 16;
int n, m, k, f[2][60000], pre[M], cur[M];
bool v[N][M];
int p[] = {1,3,9,27,81,243,729,2187,6561,19683,59049};

inline int three_ten(int *a) {
	int ans = 0;
	for (int i = 0; i < m; i++) ans += a[i] * p[i];
	return ans;
}

inline void ten_three(int x, int *a) {
	for (int i = 0; i < m; i++) {
		a[i] = x % 3;
		x /= 3;
	}
}

void dfs(int now, int j, int last, int state) {
	f[now][state] = max(f[now][state], last);
	if (j >= m) return;
	if (j + 1 < m && !pre[j] && !pre[j+1] && !cur[j] && !cur[j+1]) {
		cur[j] = cur[j+1] = 2;
		dfs(now, j + 2, last + 1, three_ten(cur));
		cur[j] = cur[j+1] = 0;
	}
	if (j + 2 < m && !cur[j] && !cur[j+1] && !cur[j+2]) {
		cur[j] = cur[j+1] = cur[j+2] = 2;
		dfs(now, j + 3, last + 1, three_ten(cur));
		cur[j] = cur[j+1] = cur[j+2] = 0;
	}
	dfs(now, j + 1, last, state);
}

int work() {
	memset(f[0], -1, sizeof(f[0]));
	for (int i = 0; i < m; i++)
		pre[i] = v[1][i] ? 2 : 1;
	int now = 0, tmp = three_ten(pre);
	f[now][tmp] = 0;
	for (int i = 2; i <= n; i++) {
		now ^= 1;
		memset(f[now], -1, sizeof(f[now]));
		for (int j = 0; j < p[m]; j++) {
			if (f[now^1][j] == -1) continue;
			ten_three(j, pre);
			for (int k = 0; k < m; k++)
				if (v[i][k]) cur[k] = 2;
				else cur[k] = pre[k] ? pre[k] - 1 : 0;
			tmp = three_ten(cur);
			dfs(now, 0, f[now^1][j], tmp);
		}
	}
	int ans = 0;
	for (int i = 0; i < p[m]; i++) ans = max(ans, f[now][i]);
	return ans;
}

void Bugs_Integrated() {
	cin >> n >> m >> k;
	memset(v, 0, sizeof(v));
	while (k--) {
		int x, y;
		scanf("%d %d", &x, &y);
		v[x][y-1] = 1;
	}
	cout << work() << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) Bugs_Integrated();
	return 0;
}
