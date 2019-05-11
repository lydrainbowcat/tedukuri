//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 100006;
int n, m, fa[N], ans[N], v[N], d[N], f[N], ANS = 0;
int Head[N], Edge[N<<1], Next[N<<1], tot = 0;
vector<pair<int, int> > q[N];
pair<int, int> Q[N];

inline void add(int x, int y) {
	Edge[++tot] = y;
	Next[tot] = Head[x];
	Head[x] = tot;
}

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

void tarjan(int x) {
	v[x] = 1;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i];
		if (v[y]) continue;
		tarjan(y);
		fa[y] = x;
	}
	for (unsigned int i = 0; i < q[x].size(); i++) {
		int y = q[x][i].first, id = q[x][i].second;
		if (v[y] == 2) ans[id] = get(y);
	}
	v[x] = 2;
}

void dfs(int x) {
	v[x] = 1;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i];
		if (v[y]) continue;
		dfs(y);
		f[x] += f[y];
	}
	f[x] += d[x];
	if (!f[x]) ANS += m;
	else if (f[x] == 1) ++ANS;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		add(x, y);
		add(y, x);
	}
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (x == y) ans[i] = x;
		else {
			q[x].push_back(make_pair(y, i));
			q[y].push_back(make_pair(x, i));
		}
		Q[i].first = x;
		Q[i].second = y;
	}
	tarjan(1);
	for (int i = 1; i <= m; i++) {
		++d[Q[i].first];
		++d[Q[i].second];
		d[ans[i]] -= 2;
	}
	memset(v, 0, sizeof(v));
	dfs(1);
	cout << ANS - m << endl;
	return 0;
}
