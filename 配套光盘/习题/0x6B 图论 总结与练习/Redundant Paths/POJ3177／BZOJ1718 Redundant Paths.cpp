//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5006, M = 20006;
int n, m, dfn[N], low[N], num;
int Head[N], Edge[M], Next[M], tot = 1;
int st[N], top = 0;
int dcc[N], deg[N], cnt, ans;
bool v[N];

inline void add(int x, int y) {
	Edge[++tot] = y;
	Next[tot] = Head[x];
	Head[x] = tot;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	for (int i = Head[x]; i; i = Next[i]) {
		if (v[i]) continue;
		int y = Edge[i];
		if (!dfn[y]) {
			st[++top] = y;
			v[i] = v[i^1] = 1;
			tarjan(y);
			v[i] = v[i^1] = 0;
			low[x] = min(low[x], low[y]);
		} else low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x]) {
		++cnt;
		while (top) {
			dcc[st[top]] = cnt;
			if (st[top--] == x) break;
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		add(x, y);
		add(y, x);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) {
			cnt = 0;
			st[top = 1] = i;
			tarjan(i);
		}
	for (int i = 2; i <= tot; i += 2) {
		int x = Edge[i], y = Edge[i+1];
		if (dcc[x] == dcc[y]) continue;
		deg[dcc[x]]++;
		deg[dcc[y]]++;
	}
	for (int i = 1; i <= n; i++)
		if (deg[i] == 1) ans++;
	cout << (ans + 1) / 2 << endl;
	return 0;
}
