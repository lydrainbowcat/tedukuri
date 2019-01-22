//Author:XuHt
#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 100006;
int n, m, t, f[N][20], dep[N], dfn[N], tot;
vector<pair<int, ll> > e[N];
ll d[N], ans;
set<pair<int, int> > st;
set<pair<int, int> >::iterator it;

inline int lca(int x, int y) {
	if (dep[x] > dep[y]) swap(x, y);
	for (int i = t; i >= 0; i--)
		if (dep[f[y][i]] >= dep[x]) y = f[y][i];
	if (x == y) return x;
	for (int i = t; i >= 0; i--)
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	return f[x][0];
}

inline ll path(int x, int y) {
	return d[x] + d[y] - (d[lca(x,y)] << 1);
}

inline void Insert(int x) {
	st.insert(make_pair(dfn[x], x));
	it = st.find(make_pair(dfn[x], x));
	set<pair<int, int> >::iterator l = it == st.begin() ? --st.end() : --it;
	it = st.find(make_pair(dfn[x], x));
	set<pair<int, int> >::iterator r = it == --st.end() ? st.begin() : ++it;
	it = st.find(make_pair(dfn[x], x));
	ans -= path((*l).second, (*r).second);
	ans += path((*l).second, (*it).second) + path((*it).second, (*r).second);
}

inline void Remove(int x) {
	it = st.find(make_pair(dfn[x], x));
	set<pair<int, int> >::iterator l = it == st.begin() ? --st.end() : --it;
	it = st.find(make_pair(dfn[x], x));
	set<pair<int, int> >::iterator r = it == --st.end() ? st.begin() : ++it;
	it = st.find(make_pair(dfn[x], x));
	ans += path((*l).second, (*r).second);
	ans -= path((*l).second, (*it).second) + path((*it).second, (*r).second);
	st.erase(make_pair(dfn[x], x));
}

void dfs(int x) {
	dfn[x] = ++tot;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first;
		if (dep[y]) continue;
		dep[y] = dep[x] + 1;
		ll z = e[x][i].second;
		d[y] = d[x] + z;
		f[y][0] = x;
		for (int j = 1; j <= t; j++)
			f[y][j] = f[f[y][j-1]][j-1];
		dfs(y);
	}
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int x, y;
		ll z;
		scanf("%d %d %lld", &x, &y, &z);
		e[x].push_back(make_pair(y, z));
		e[y].push_back(make_pair(x, z));
	}
	t = log(n) / log(2) + 1;
	dep[1] = 1;
	dfs(1);
	cin >> m;
	while (m--) {
		char s[2];
		scanf("%s", s);
		if (s[0] == '?') printf("%lld\n", ans >> 1);
		else {
			int x;
			scanf("%d", &x);
			s[0] == '+' ? Insert(x) : Remove(x);
		}
	}
	return 0;
}
