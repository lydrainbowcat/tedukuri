//Author:XuHt
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;
const int N = 500006;
int n, m, t, f[N][20], deg[N];
int pos[N], cnt, len[N], s[N];
int d[N], id[N];
vector<int> e[N];
queue<int> q;

inline void prework() {
	t = log(n) / log(2);
	for (int i = 1; i <= t; i++)
		for (int x = 1; x <= n; x++)
			f[x][i] = f[f[x][i-1]][i-1];
}

inline void topsort() {
	for (int i = 1; i <= n; i++)
		if (!deg[i]) q.push(i);
	while (q.size()) {
		int x = q.front();
		q.pop();
		if (!--deg[f[x][0]]) q.push(f[x][0]);
	}
}

inline void bfs() {
	for (int i = 1; i <= n; i++)
		if (pos[i]) {
			id[i] = i;
			q.push(i);
		} else e[f[i][0]].push_back(i);
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (unsigned int i = 0; i < e[x].size(); i++) {
			int y = e[x][i];
			d[y] = d[x] + 1;
			id[y] = id[x];
			q.push(y);
		}
	}
}

inline int lca(int x, int y) {
	if (d[x] > d[y]) swap(x, y);
	for (int i = 19; i >= 0; i--)
		if (d[f[y][i]] >= d[x]) y = f[y][i];
	if (x == y) return x;
	for (int i = 19; i >= 0; i--)
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	return f[x][0];
}

inline pii cmp(pii a, pii b) {
	if (max(a.x, a.y) < max(b.x, b.y)) return a;
	if (max(a.x, a.y) > max(b.x, b.y)) return b;
	if (min(a.x, a.y) < min(b.x, b.y)) return a;
	if (min(a.x, a.y) > min(b.x, b.y)) return b;
	return a.x >= a.y ? a : b;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &f[i][0]);
		deg[f[i][0]]++;
	}
	prework();
	topsort();
	for (int i = 1; i <= n; i++)
		if (deg[i] && !pos[i]) {
			++cnt;
			for (int j = i; !pos[j]; j = f[j][0]) {
				pos[j] = cnt;
				s[j] = ++len[cnt];
			}
		}
	bfs();
	while (m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (pos[id[x]] != pos[id[y]]) puts("-1 -1");
		else if (id[x] == id[y]) {
			int p = lca(x, y);
			printf("%d %d\n", d[x] - d[p], d[y] - d[p]);
		} else {
			pii a, b;
			int sx = s[id[x]], sy = s[id[y]], now = len[pos[id[x]]];
			a.x = d[x] + (sy - sx + now) % now;
			a.y = d[y];
			b.x = d[x];
			b.y = d[y] + (sx - sy + now) % now;
			pii ans = cmp(a, b);
			printf("%d %d\n", ans.x, ans.y);
		}
	}
	return 0;
}
