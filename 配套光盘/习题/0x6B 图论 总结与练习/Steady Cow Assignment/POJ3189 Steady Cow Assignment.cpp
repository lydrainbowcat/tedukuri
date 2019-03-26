//Author:xht37
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e3 + 6, M = 22, inf = 1e9;
int n, m, a[N][M], c[M], ans;
int Head[N+M], Edge[N*M<<1], Leng[N*M<<1], Next[N*M<<1], tot;
int d[N+M];

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

inline bool bfs() {
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(0);
	d[0] = 1;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i], z = Leng[i];
			if (d[y] || !z) continue;
			q.push(y);
			d[y] = d[x] + 1;
			if (y == n + m + 1) return 1;
		}
	}
	return 0;
}

int dinic(int x, int flow) {
	if (x == n + m + 1) return flow;
	int rest = flow;
	for (int i = Head[x]; i && rest; i = Next[i]) {
		int y = Edge[i], z = Leng[i];
		if (d[y] != d[x] + 1 || !z) continue;
		int k = dinic(y, min(rest, z));
		if (!k) d[y] = 0;
		else {
			Leng[i] -= k;
			Leng[i^1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}

inline bool work(int l, int r) {
	tot = 1;
	for (int i = 0; i <= n + m + 1; i++) Head[i] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = l; j <= r; j++) {
			add(i, n + a[i][j], 1);
			add(n + a[i][j], i, 0);
		}
	for (int i = 1; i <= n; i++) {
		add(0, i, 1);
		add(i, 0, 0);
	}
	for (int i = 1; i <= m; i++) {
		add(n + i, n + m + 1, c[i]);
		add(n + m + 1, n + i, 0);
	}
	int now = 0, ans = 0;
	while (bfs())
		while ((now = dinic(0, inf))) ans += now;
	return ans == n;
}

inline bool pd(int now) {
	for (int l = 1; l + now - 1 <= m; l++)
		if (work(l, l + now - 1)) return 1;
	return 0;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for (int i = 1; i <= m; i++)
		scanf("%d", &c[i]);
	ans = m;
	int l = 1, r = m - 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (pd(mid)) {
			ans = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
