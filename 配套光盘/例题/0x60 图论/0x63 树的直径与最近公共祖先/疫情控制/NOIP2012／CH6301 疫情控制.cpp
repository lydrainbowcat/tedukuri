//Author:XuHt
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 50006;
int head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], tot;
int n, m, t, a[N], b[N], g[N], fa[N][16], sh[N];
ll c[N], d[N], f[N], dis[N][16], sum;
vector<ll> arv[N];
queue<int> q;
bool v[N], w[N];

void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = head[x];
	head[x] = tot;
}

void bfs() {
	v[1] = 1;
	for (int i = head[1]; i; i = Next[i]) {
		int y = Edge[i];
		q.push(y);
		v[y] = 1;
		b[sh[y]=++t] = i;
	}
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			int y = Edge[i];
			if (v[y]) continue;
			q.push(y);
			v[y] = 1;
			fa[y][0] = x;
			dis[y][0] = Leng[i];
			for (int j = 1; j < 16; j++) {
				fa[y][j] = fa[fa[y][j-1]][j-1];
				dis[y][j] = dis[y][j-1] + dis[fa[y][j-1]][j-1];
			}
		}
	}
}

bool dfs(int x) {
	v[x] = 1;
	if (!sh[x] && w[x]) return 1;
	bool flag = 0;
	for (int i = head[x]; i; i = Next[i]) {
		int y = Edge[i];
		if (v[y]) continue;
		flag = 1;
		if (!dfs(Edge[i])) return 0;
	}
	return flag;
}

bool work(ll now) {
	for (int i = 1; i <= t; i++) arv[i].clear();
	memset(v, 0, sizeof(v));
	memset(w, 0, sizeof(w));
	v[1] = 1;
	for (int i = 1; i <= m; i++) {
		g[i] = a[i];
		d[i] = 0;
		for (int j = 15; j >= 0; j--)
			if (fa[g[i]][j] && d[i] + dis[g[i]][j] <= now) {
				d[i] += dis[g[i]][j];
				g[i] = fa[g[i]][j];
			}
		w[g[i]] = 1;
		int j = sh[g[i]];
		if (j) {
			arv[j].push_back(now - d[i]);
			if (arv[j].size() > 1 && now - d[i] > arv[j][arv[j].size()-2])
				swap(arv[j][arv[j].size()-1], arv[j][arv[j].size()-2]);
		}
	}
	int p = 0, q = 0;
	for (int i = 1; i <= t; i++) {
		if (!dfs(Edge[b[i]])) {
			if (arv[i].size() && arv[i][arv[i].size()-1] < (Leng[b[i]] << 1))
				arv[i].pop_back();
			else f[++q] = Leng[b[i]];
		}
		for (unsigned int j = 0; j < arv[i].size(); j++)
			if (arv[i][j] >= Leng[b[i]])
				c[++p] = arv[i][j] - Leng[b[i]];
	}
	sort(c + 1, c + p + 1);
	sort(f + 1, f + q + 1);
	if (p < q) return 0;
	for (int i = q, j = p; i; i--, j--)
		if (c[j] < f[i]) return 0;
	return 1;
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
		sum += z;
	}
	cin >> m;
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	bfs();
	ll l = 0, r = sum + 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (work(mid)) r = mid;
		else l = mid + 1;
	}
	if (l > sum) puts("-1");
	else cout << l << endl;
	return 0;
}
