#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N = 20010, M = 200010;
int head[N], ver[M], Next[M];
int dfn[N], low[N], stack[N], new_id[N], c[N], belong[M];
int d[N], dist[N], f[N][16];
int n, m, t, tot, num, root, top, cnt, tc;
bool cut[N];
vector<int> dcc[N];
int hc[N], vc[M], nc[M];
queue<int> q;

void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void add_c(int x, int y) {
	vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	stack[++top] = x;
	if (x == root && head[x] == 0) { // 孤立点
		dcc[++cnt].push_back(x);
		return;
	}
	int flag = 0;
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x]) {
				flag++;
				if (x != root || flag > 1) cut[x] = true;
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

void bfs(int s) {
	q.push(s); d[s] = 1; dist[s] = (s > cnt);
	for (int i = 0; i < 16; i++) f[s][i] = 0;
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = hc[x]; i; i = nc[i]) {
			int y = vc[i];
			if (d[y]) continue;
			d[y] = d[x] + 1;
			dist[y] = dist[x] + (y > cnt);
			f[y][0] = x;
			for (int j = 1; j < 16; j++)
				f[y][j] = f[f[y][j - 1]][j - 1];
			q.push(y);
		}
	}
}

int lca(int x, int y) {
	if (d[x] < d[y]) swap(x, y);
	for (int i = 15; i >= 0; i--)
		if (d[f[x][i]] >= d[y]) x = f[x][i];
	if (x == y) return x;
	for (int i = 15; i >= 0; i--)
		if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}

int main() {
	while (cin >> n >> m && n) {
		memset(head, 0, sizeof(head));
		memset(hc, 0, sizeof(hc));
		memset(dfn, 0, sizeof(dfn));
		memset(d, 0, sizeof(d));
		memset(cut, 0, sizeof(cut));
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; i++) dcc[i].clear();
		tot = 1; num = cnt = top = 0;
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			add(x, y), add(y, x);
		}
		for (int i = 1; i <= n; i++)
			if (!dfn[i]) root = i, tarjan(i);
		// 给每个割点一个新的编号(编号从cnt+1开始)
		num = cnt;
		for (int i = 1; i <= n; i++)
			if (cut[i]) new_id[i] = ++num;
		// 建新图，从每个v-DCC到它包含的所有割点连边
		// 同时求出原图的每条边分别属于哪一个v-DCC
		tc = 1;
		for (int i = 1; i <= cnt; i++) {
			for (int j = 0; j < dcc[i].size(); j++) {
				int x = dcc[i][j];
				if (cut[x]) {
					add_c(i, new_id[x]);
					add_c(new_id[x], i);
				}
				c[x] = i;
			}
			for (int j = 0; j < dcc[i].size() - 1; j++) {
				int x = dcc[i][j];
				for (int k = head[x]; k; k = Next[k]) {
					int y = ver[k];
					// 输入的第k/2条边(x,y)处于第i个v-DCC内
					if (c[y] == i) belong[k / 2] = i;
				}
			}
		}
		// 缩点后的图，共 num 个点
		// 编号 1~cnt 的为原图的v-DCC，编号 cnt+1~num 的为原图割点
		for (int i = 1; i <= num; i++)
			if (!d[i]) bfs(i);
		cin >> t;
		while (t--) {
			int es, et;
			scanf("%d%d", &es, &et);
			int x = belong[es], y = belong[et];
			int z = lca(x, y);
			printf("%d\n", dist[x] + dist[y] - 2 * dist[z] + (z>cnt));
		}
	}
}

