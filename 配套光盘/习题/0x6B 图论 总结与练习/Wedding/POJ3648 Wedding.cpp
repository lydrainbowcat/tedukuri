//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 206, M = 100006;
int n, m, dfn[N], low[N], num;
int Head[N], Edge[M], Next[M], tot;
int c[N], cnt, deg[N], st[N], top;
bool ins[N];
int vx[M], vy[M], t, p[N], ans[N];

inline void add(int x, int y) {
	if (!num) {
		vx[++t] = x;
		vy[t] = y;
	} else deg[y]++;
	Edge[++tot] = y;
	Next[tot] = Head[x];
	Head[x] = tot;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	st[++top] = x;
	ins[x] = 1;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (ins[y]) low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x]) {
		cnt++;
		int y;
		do {
			y = st[top--];
			ins[y] = 0;
			c[y] = cnt;
		} while (x != y);
	}
}

void topsort() {
	queue<int> q;
	memset(Head, 0, sizeof(Head));
	memset(ans, 0, sizeof(ans));
	memset(deg, 0, sizeof(deg));
	tot = 0;
	for (int i = 1; i <= t; i++)
		if (c[vx[i]] != c[vy[i]])
			add(c[vy[i]], c[vx[i]]);
	for (int i = 1; i <= cnt; i++)
		if (!deg[i]) q.push(i);
	while (q.size()) {
		int x = q.front();
		q.pop();
		if (!ans[x]) {
			ans[x] = 1;
			ans[p[x]] = 2;
		}
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i];
			if (!--deg[y]) q.push(y);
		}
	}
	if (ans[c[1]] == 1) printf("1w");
	else printf("1h");
	for (int i = 2; i < n; i++)
		if (ans[c[i]] == 1) printf(" %dw",i);
		else printf(" %dh",i);
	puts("");
}

void work() {
	memset(Head, 0, sizeof(Head));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	tot = num = top = cnt = t = 0;
	add(2 * n, 0);
	add(n, 3 * n);
	for (int i = 1; i < n; i++) {
		add(i, n * 3 + i);
		add(n * 2 + i, n + i);
		add(n + i, n * 2 + i);
		add(n * 3 + i, i);
	}
	for (int i = 1; i <= m; i++) {
		int x, y;
		char cx, cy;
		scanf("%d%c %d%c", &x, &cx, &y, &cy);
		cx = (cx == 'w') ? 0 : n;
		cy = (cy == 'w') ? 0 : n;
		add(cx + 2 * n + x, cy + y);
		add(cy + 2 * n + y, cx + x);
	}
	for (int i = 0; i < 4 * n; i++)
		if (!dfn[i]) tarjan(i);
	for (int i = 0; i < 2 * n; i++) {
		if (c[i] == c[2*n+i]) {
			puts("bad luck");
			return;
		}
		p[c[i]] = c[2*n+i];
		p[c[2*n+i]] = c[i];
	}
	topsort();
}

int main() {
	while (cin >> n >> m && n && m) work();
	return 0;
}
