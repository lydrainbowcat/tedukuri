//Author:XuHt
#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 37, INF = 0x3f3f3f3f;
struct E {
	int x, y, z;
	bool operator < (const E w) const {
		return z < w.z;
	}
} f[N];
int n, k, tot, ans, a[N][N], fa[N], d[N], v[N];
map<string, int> m;
vector<E> e;
bool b[N][N];

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

void dfs(int x, int o) {
	for (int i = 2; i <= tot; i++) {
		if (i == o || !b[x][i]) continue;
		if (f[i].z == -1) {
			if (f[x].z > a[x][i]) f[i] = f[x];
			else {
				f[i].x = x;
				f[i].y = i;
				f[i].z = a[x][i];
			}
		}
		dfs(i, x);
	}
}

int main() {
	cin >> n;
	memset(a, 0x3f, sizeof(a));
	memset(d, 0x3f, sizeof(d));
	m["Park"] = tot = 1;
	for (int i = 0; i < N; i++) fa[i] = i;
	for (int i = 1; i <= n; i++) {
		E w;
		string s1, s2;
		cin >> s1 >> s2 >> w.z;
		w.x = m[s1] ? m[s1] : (m[s1] = ++tot);
		w.y = m[s2] ? m[s2] : (m[s2] = ++tot);
		e.push_back(w);
		a[w.x][w.y] = a[w.y][w.x] = min(a[w.x][w.y], w.z);
	}
	cin >> k;
	sort(e.begin(), e.end());
	for (unsigned int i = 0; i < e.size(); i++) {
		if (e[i].x == 1 || e[i].y == 1) continue;
		int rtx = get(e[i].x), rty = get(e[i].y);
		if (rtx != rty) {
			fa[rtx] = rty;
			b[e[i].x][e[i].y] = b[e[i].y][e[i].x] = 1;
			ans += e[i].z;
		}
	}
	for (int i = 2; i <= tot; i++)
		if (a[1][i] != INF) {
			int rt = get(i);
			if (d[rt] > a[1][i]) d[rt] = a[1][v[rt]=i];
		}
	for (int i = 1; i <= tot; i++)
		if (d[i] != INF) {
			--k;
			b[1][v[i]] = b[v[i]][1] = 1;
			ans += a[1][v[i]];
		}
	while (k--) {
		memset(f, -1, sizeof(f));
		f[1].z = -INF;
		for (int i = 2; i <= tot; i++)
			if (b[1][i]) f[i].z = -INF;
		dfs(1, -1);
		int o, w = -INF;
		for (int i = 2; i <= tot; i++)
			if (w < f[i].z - a[1][i])
				w = f[i].z - a[1][o=i];
		if (w <= 0) break;
		b[1][o] = b[o][1] = 1;
		b[f[o].x][f[o].y] = b[f[o].y][f[o].x] = 0;
		ans -= w;
	}
	printf("Total miles driven: %d\n", ans);
	return 0;
}
