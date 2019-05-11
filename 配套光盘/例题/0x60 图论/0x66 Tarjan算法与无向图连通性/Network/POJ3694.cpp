#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int SIZE = 200010;
int head[SIZE], ver[SIZE * 2], Next[SIZE * 2];
int dfn[SIZE], low[SIZE], c[SIZE];
int n, m, t, tot, num, dcc, tc, T;
bool bridge[SIZE * 2], v[SIZE];
int hc[SIZE], vc[SIZE * 2], nc[SIZE * 2];
int d[SIZE], f[SIZE][20], fa[SIZE];
queue<int> q;

void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void add_c(int x, int y) {
	vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

void tarjan(int x, int in_edge) {
	dfn[x] = low[x] = ++num;
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y, i);
			low[x] = min(low[x], low[y]);
			if (low[y] > dfn[x])
				bridge[i] = bridge[i ^ 1] = true;
		}
		else if (i != (in_edge ^ 1))
			low[x] = min(low[x], dfn[y]);
	}
}

void dfs(int x) {
	c[x] = dcc;
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (c[y] || bridge[i]) continue;
		dfs(y);
	}
}

void bfs() {
	q.push(1);
	d[1] = 1;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = hc[x]; i; i = nc[i]) {
			int y = vc[i];
			if (d[y]) continue;
			d[y] = d[x] + 1;
			f[y][0] = x;
			for (int j = 1; j < 18; j++)
				f[y][j] = f[f[y][j - 1]][j - 1];
			q.push(y);
		}
	}
}

int lca(int x, int y) {
	if (d[x] < d[y]) swap(x, y);
	for (int i = 17; i >= 0; i--)
		if (d[f[x][i]] >= d[y]) x = f[x][i];
	if (x == y) return x;
	for (int i = 17; i >= 0; i--)
		if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

int main() {
	while (cin >> n >> m && n) {
		// 多组数据，清零
		tot = 1; num = dcc = 0;
		for (int i = 1; i <= n; i++)
			head[i] = dfn[i] = hc[i] = d[i] = c[i] = 0;
		for (int i = 1; i <= 2 * m + 1; i++)
			bridge[i] = 0;
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			add(x, y), add(y, x);
		}
		// 求割边、边双连通分量
		for (int i = 1; i <= n; i++)
			if (!dfn[i]) tarjan(i, 0);
		for (int i = 1; i <= n; i++)
			if (!c[i]) {
				++dcc;
				dfs(i);
			}
		// 缩点建图
		tc = 1;
		for (int i = 2; i <= tot; i++) {
			int x = ver[i ^ 1], y = ver[i];
			if (c[x] == c[y]) continue;
			add_c(c[x], c[y]);
		}
		// 倍增lca预处理
		bfs();
		// 并查集初始化
		for (int i = 1; i <= dcc; i++) fa[i] = i;
		// 处理询问
		cin >> t;
		int ans = dcc - 1;
		printf("Case %d:\n", ++T);
		while (t--) {
			int x, y;
			scanf("%d%d", &x, &y);
			x = c[x], y = c[y];
			int p = lca(x, y);
			x = get(x);
			while (d[x] > d[p]) {
				fa[x] = f[x][0];
				ans--;
				x = get(x);
			}
			y = get(y);
			while (d[y] > d[p]) {
				fa[y] = f[y][0];
				ans--;
				y = get(y);
			}
			printf("%d\n", ans);
		}
		cout << endl;
	}
}