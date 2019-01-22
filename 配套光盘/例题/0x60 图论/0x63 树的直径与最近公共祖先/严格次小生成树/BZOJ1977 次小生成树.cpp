//Author:XuHt
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 100006, M = 300006;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m, t, fa[N], d[N], f[N][20];
struct P {
	int x, y;
	ll z;
	bool k;
	bool operator < (const P w) const {
		return z < w.z;
	}
} p[M];
ll g[N][20][2], sum, ans = INF;
vector<pair<int, ll> > e[N];

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

void kruskal() {
	sort(p + 1, p + m + 1);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int x = get(p[i].x), y = get(p[i].y);
		if (x == y) continue;
		fa[x] = y;
		sum += p[i].z;
		p[i].k = 1;
	}
}

void dfs(int x) {
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first;
		if (d[y]) continue;
		d[y] = d[x] + 1;
		f[y][0] = x;
		int z = e[x][i].second;
		g[y][0][0] = z;
		g[y][0][1] = -INF;
		for (int j = 1; j <= t; j++) {
			f[y][j] = f[f[y][j-1]][j-1];
			g[y][j][0] = max(g[y][j-1][0], g[f[y][j-1]][j-1][0]);
			if (g[y][j-1][0] == g[f[y][j-1]][j-1][0])
				g[y][j][1] = max(g[y][j-1][1], g[f[y][j-1]][j-1][1]);
			else if (g[y][j-1][0] < g[f[y][j-1]][j-1][0])
				g[y][j][1] = max(g[y][j-1][0], g[f[y][j-1]][j-1][1]);
			else g[y][j][1] = max(g[y][j-1][1], g[f[y][j-1]][j-1][0]);
		}
		dfs(y);
	}
}

inline void lca(int x, int y, ll &val1, ll &val2) {
	if (d[x] > d[y]) swap(x, y);
	for (int i = t; i >= 0; i--)
		if (d[f[y][i]] >= d[x]) {
			if (val1 > g[y][i][0]) val2 = max(val2, g[y][i][0]);
			else {
				val1 = g[y][i][0];
				val2 = max(val2, g[y][i][1]);
			}
			y = f[y][i];
		}
	if (x == y) return;
	for (int i = t; i >= 0; i--)
		if (f[x][i] != f[y][i]) {
			val1 = max(val1, max(g[x][i][0], g[y][i][0]));
			val2 = max(val2, g[x][i][0] != val1 ? g[x][i][0] : g[x][i][1]);
			val2 = max(val2, g[y][i][0] != val1 ? g[y][i][0] : g[y][i][1]);
			x = f[x][i];
			y = f[y][i];
		}
	val1 = max(val1, max(g[x][0][0], g[y][0][0]));
	val2 = max(val2, g[x][0][0] != val1 ? g[x][0][0] : g[x][0][1]);
	val2 = max(val2, g[y][0][0] != val1 ? g[y][0][0] : g[y][0][1]);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %lld", &p[i].x, &p[i].y, &p[i].z);
		p[i].k = 0;
	}
	kruskal();
	for (int i = 1; i <= m; i++)
		if (p[i].k) {
			e[p[i].x].push_back(make_pair(p[i].y, p[i].z));
			e[p[i].y].push_back(make_pair(p[i].x, p[i].z));
		}
	t = log(n) / log(2) + 1;
	d[1] = 1;
	for (int i = 0; i <= t; i++) g[1][i][0] = g[1][i][1] = -INF;
	dfs(1);
	for (int i = 1; i <= m; i++)
		if (!p[i].k) {
			ll val1 = -INF, val2 = -INF;
			lca(p[i].x, p[i].y, val1, val2);
			if (p[i].z > val1) ans = min(ans, sum - val1 + p[i].z);
			else ans = min(ans, sum - val2 + p[i].z);
		}
	cout << ans << endl;
	return 0;
}
