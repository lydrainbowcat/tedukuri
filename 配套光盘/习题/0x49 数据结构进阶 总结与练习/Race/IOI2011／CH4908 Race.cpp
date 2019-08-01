//Author:xht37
#include <bits/stdc++.h>
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ui unsigned int
using namespace std;

const int N = 2e5 + 6, K = 1e6 + 6, inf = 1e9;
int n, k, ans = inf, rt, sz, s[N], t[N], c[K], st[N], tp;
vector< pii > e[N];
bool v[N];

void getrt(int x, int f) {
    s[x] = 1;
	t[x] = 0;
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first;
		if (v[y] || y == f) continue;
		getrt(y, x);
		s[x] += s[y];
		t[x] = max(t[x], s[y]);
	}
    t[x] = max(t[x], sz - s[x]);
    if (t[rt] > t[x]) rt = x;
}

inline void add(int x, int o) {
    st[++tp] = x;
    c[x] = min(c[x], o);
}

void ask(int x, int f, int dis, int cnt) {
    if (dis > k) return;
    ans = min(ans, cnt + c[k-dis]);
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i].fi, z = e[x][i].se;
		if (v[y] || y == f) continue;
		ask(y, x, dis + z, cnt + 1);
	}
}

void upd(int x, int f, int dis, int cnt) {
    if (dis > k) return;
    st[++tp] = dis;
    c[dis] = min(c[dis], cnt);
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i].fi, z = e[x][i].se;
		if (v[y] || y == f) continue;
		upd(y, x, dis + z, cnt + 1);
	}
}

void dfs(int x) {
    v[x] = 1;
    st[++tp] = 0;
    c[0] = min(c[0], 0);
    for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i].fi, z = e[x][i].se;
		if (v[y]) continue;
		ask(y, x, z, 1);
		upd(y, x, z, 1);
	}
    while (tp) c[st[tp--]] = inf;
    for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i].fi;
		if (v[y]) continue;
		rt = 0;
		sz = s[y];
		getrt(y, 0);
		dfs(rt);
	}
}

int main() {
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		e[++x].pb(mp(++y, z));
		e[y].pb(mp(x, z));
	}
	for (int i = 0; i <= k; i++) c[i] = inf;
    t[0] = inf;
	sz = n;
	getrt(1, 0);
    dfs(rt);
    cout << (ans == inf ? -1 : ans) << endl;
    return 0;
}
