//Author:XuHt
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 10006, M = 100006;
int n, m, q, t, cnt;
int d[N], dep[N], dfn[N], pos[N], f[N][14], s[N], a[N], b[N];
int Head[N], Next[M], Edge[M], Leng[M], tot = 1;
bool v[N], w[M];

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

void spfa() {
	memset(d, 0x3f, sizeof(d));
	queue<int> q;
	q.push(1);
	d[1] = 0;
	while (q.size()) {
		int x = q.front();
		q.pop();
		v[x] = 0;
		for (int i = Head[x]; i; i = Next[i])
			if (d[Edge[i]] > d[x] + Leng[i]) {
				d[Edge[i]] = d[x] + Leng[i];
				if (!v[Edge[i]]) {
					v[Edge[i]] = 1;
					q.push(Edge[i]);
				}
			}
	}
}

void work(int x, int y) {
	if (x == y) return;
	pos[x] = cnt;
	add(y, x, 0);
	w[a[x]] = w[a[x]^1] = 1;
	s[cnt] += Leng[a[x]];
	work(Edge[a[x]^1], y);
}

void dfs1(int x) {
	dfn[x] = ++t;
	for (int i = Head[x]; i; i = Next[i])
		if (i != (a[x] ^ 1) && i <= (m << 1 | 1)) {
			if (!dfn[Edge[i]]) {
				b[Edge[i]] = b[x] + Leng[i];
				a[Edge[i]] = i;
				dfs1(Edge[i]);
			} else if (dfn[Edge[i]] < dfn[x]) {
				s[++cnt] = Leng[i];
				work(x, Edge[i]);
			}
		}
}

void dfs2(int x) {
	for (int i = Head[x]; i; i = Next[i])
		if (!w[i] && !dep[Edge[i]]) {
			f[Edge[i]][0] = x;
			dep[Edge[i]] = dep[x] + 1;
			dfs2(Edge[i]);
		}
}

int ask(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int o = x, p = y;
	for (int i = 13; i >= 0; i--)
		if(dep[f[x][i]] >= dep[y]) x = f[x][i];
	if (x == y) return d[o] - d[p];
	for (int i = 13; i >= 0; i--)
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	if (pos[x] && pos[x] == pos[y]) {
		int now = abs(b[x] - b[y]);
		return d[o] - d[x] + d[p] - d[y] + min(now, s[pos[x]] - now);
	}
	return d[o] + d[p] - 2 * d[f[x][0]];
}

int main() {
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
	}
	spfa();
	dfs1(1);
	dep[1] = 1;
	dfs2(1);
	for (int j = 1; j < 14; j++)
		for (int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j-1]][j-1];
	while (q--) {
		int x, y;
		scanf("%d %d", &x, &y);
		printf("%d\n", ask(x, y));
	}
	return 0;
}
