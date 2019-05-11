//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006, M = 300006;
int n, m, low[N], dfn[N], num, deg[N];
int Head[N], Edge[M], Next[M], tot;
int Headc[N], Edgec[M], Nextc[M], totc;
int st[N], top, c[N], cnt[N], scc;
bool ins[N], v[N];

inline void add(int x, int y) {
	Edge[++tot] = y;
	Next[tot] = Head[x];
	Head[x] = tot;
}

inline void addc(int x, int y) {
	Edgec[++totc] = y;
	Nextc[totc] = Headc[x];
	Headc[x] = totc;
	deg[y]++;
}

void tarjan(int x) {
	low[x] = dfn[x] = ++num;
	ins[x] = 1;
	st[++top] = x;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (ins[y]) low[x] = min(low[x], dfn[y]);
	}
	if (low[x] == dfn[x]) {
		++scc;
		int y;
		do {
			y = st[top--];
			ins[y] = 0;
			c[y] = scc;
			cnt[scc]++;
		} while (x != y);
	}
}

inline bool pd(int x) {
	if (deg[x] || cnt[x] != 1) return 0;
	for (int i = Headc[x]; i; i = Nextc[i]) {
		int y = Edgec[i];
		if (deg[y] == 1) return 0;
	}
	return 1;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		add(x, y);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i);
	for (int x = 1; x <= n; x++) {
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i];
			if (c[x] == c[y] || v[c[y]]) continue;
			v[c[y]] = 1;
			addc(c[x], c[y]);
		}
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i];
			v[c[y]] = 0;
		}
	}
	int ans = 0;
	for (int i = 1; i <= scc; i++)
		if (!deg[i]) ans++;
	for (int i = 1; i <= scc; i++)
		if (pd(i)) {
			ans--;
			break;
		}
	printf("%.6lf\n", (double)(n - ans) / n);
	return 0;
}
