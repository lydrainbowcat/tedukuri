//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2006, M = 100006;
int n, m, u[M], v[M], a[N], p[N];
int dfn[N], low[N], num;
int Head[N], Edge[M], Next[M], tot;
int st[N], top, c[N], cnt;
bool ins[N];

inline void add(int x, int y) {
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
	if (low[x] == dfn[x]) {
		++cnt;
		int y;
		do {
			y = st[top--];
			ins[y] = 0;
			c[y] = cnt;
		} while (x != y);
	}
}

inline bool pd() {
	for (int i = 1; i <= m; i++)
		if (c[2*i] == c[2*i-1]) return 0;
	return 1;
}

inline void work() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) scanf("%d %d", &u[i], &v[i]);
	tot = cnt = num = top = 0;
	memset(Head, 0, sizeof(Head));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	if (m + 6 > 3 * n) {
		puts("NO");
		return;
	}
	for (int i = 1; i <= n; i++) p[a[i]] = i;
	for (int i = 1; i <= m; i++) {
		u[i] = p[u[i]];
		v[i] = p[v[i]];
		if (u[i] > v[i]) swap(u[i], v[i]);
		if (v[i] - u[i] == 1 || (v[i] == n && u[i] == 1)) continue;
		u[++top] = u[i];
		v[top] = v[i];
	}
	m = top;
	for (int i = 1; i <= m; i++)
		for (int j = i + 1; j <= m; j++)
			if ((u[i] < u[j] && u[j] < v[i] && v[i] < v[j]) || (u[j] < u[i] && u[i] < v[j] && v[j] < v[i])) {
				add(2 * i - 1, 2 * j);
				add(2 * i, 2 * j - 1);
				add(2 * j - 1, 2 * i);
				add(2 * j, 2 * i - 1);
			}
	top = 0;
	for (int i = 1; i <= (m << 1); i++)
		if (!dfn[i]) tarjan(i);
	puts(pd() ? "YES" : "NO");
}

int main() {
	int t;
	cin >> t;
	while (t--) work();
	return 0;
}
