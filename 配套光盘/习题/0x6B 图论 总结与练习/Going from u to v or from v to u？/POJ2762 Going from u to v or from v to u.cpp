//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006, M = 6006;
int n, m, dfn[N], low[N], num, c[N], deg[N], cnt;
int Head[N], Edge[M], Next[M], tot;
int Headc[N], Edgec[M], Nextc[M], totc;
int st[N], top;
bool ins[N];

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
		++cnt;
		int y;
		do {
			y = st[top--];
			ins[y] = 0;
			c[y] = cnt;
		} while (x != y);
	}
}

inline bool topsort() {
	queue<int> q;
	for (int i = 1; i <= cnt; i++)
		if (!deg[i]) q.push(i);
	if (q.size() > 1) return 0;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = Headc[x]; i; i = Nextc[i]) {
			int y = Edgec[i];
			if (!--deg[y]) q.push(y);
		}
		if (q.size() > 1) return 0;
	}
	return 1;
}

inline void work() {
	cin >> n >> m;
	tot = totc = 1;
	num = cnt = top = 0;
	memset(Head, 0, sizeof(Head));
	memset(Headc, 0, sizeof(Headc));
	memset(ins, 0, sizeof(ins));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(deg, 0, sizeof(deg));
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		add(x, y);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i);
	for (int x = 1; x <= n; x++)
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i];
			if (c[x] != c[y]) addc(c[x], c[y]);
		}
	puts(topsort() ? "Yes" : "No");
}

int main() {
	int t;
	cin >> t;
	while (t--) work();
	return 0;
}
