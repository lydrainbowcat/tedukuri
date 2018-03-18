#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 1010, M = 2000010;
int head[N], ver[M], Next[M];
int dfn[N], low[N], stack[N];
int c[N], v[N], able[N];
int n, m, tot, num, top, cnt, now;
bool hate[N][N], flag;
vector<int> dcc[N];

void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int x, int root) {
	dfn[x] = low[x] = ++num;
	stack[++top] = x;
	if (x == root && head[x] == 0) { // 孤立点
		dcc[++cnt].push_back(x);
		return;
	}
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y, root);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x]) {
				cnt++;
				int z;
				do {
					z = stack[top--];
					dcc[cnt].push_back(z);
				} while (z != y);
				dcc[cnt].push_back(x);
			}
		}
		else low[x] = min(low[x], dfn[y]);
	}
}

void dfs(int x, int color) {
	c[x] = color;
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (v[y] != now) continue;
		if (c[y] && c[y] == color) {
			flag = 1;
			return;
		}
		if (!c[y]) dfs(y, 3 - color);
	}
}

int main() {
	while (cin >> n >> m && n) {
		// 清零
		memset(head, 0, sizeof(head));
		memset(dfn, 0, sizeof(dfn));
		memset(able, 0, sizeof(able));
		memset(v, 0, sizeof(v));
		for (int i = 1; i <= n; i++) dcc[i].clear();
		tot = 1; num = top = cnt = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) hate[i][j] = 0;
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			if (x == y) continue;
			hate[x][y] = hate[y][x] = 1;
		}
		// 建补图
		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n; j++)
				if (!hate[i][j]) add(i, j), add(j, i);
		// 求点双连通分量
		for (int i = 1; i <= n; i++)
			if (!dfn[i]) tarjan(i, i);
		// 判断每个点双是否包含奇环
		for (int i = 1; i <= cnt; i++) {
			now = i;
			for (int j = 0; j < dcc[i].size(); j++)
				v[dcc[i][j]] = now, c[dcc[i][j]] = 0;
			flag = false;
			dfs(dcc[i][0], 1);
			if (flag)
				for (int j = 0; j < dcc[i].size(); j++)
					able[dcc[i][j]] = 1;
		}
		int ans = 0;
		for (int i = 1; i <= n; i++)
			if (!able[i]) ans++;
		cout << ans << endl;
	}
}