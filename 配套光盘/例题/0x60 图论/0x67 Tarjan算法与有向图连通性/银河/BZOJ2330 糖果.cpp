//Author:XuHt
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 100006;
int n, m, num, top, cnt;
int d[N], dfn[N], low[N], st[N], c[N], deg[N], f[N], scc[N];
bool ins[N];
vector<pair<int, int> > e[N], ec[N];
queue<int> q;

inline void add(int x, int y, int z) {
	e[x].push_back(make_pair(y, z));
}

inline void addc(int x, int y, int z) {
	ec[x].push_back(make_pair(y, z));
	++deg[y];
}

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	st[++top] = x;
	ins[x] = 1;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first;
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (ins[y])
			low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x]) {
		++cnt;
		int y;
		do {
			y = st[top--];
			ins[y] = 0;
			c[y] = cnt;
			++scc[cnt];
		} while (y != x);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int o, a, b;
		scanf("%d %d %d", &o, &a, &b);
		if (o == 2) add(a, b, 1);
		else if (o == 3) add(b, a, 0);
		else if (o == 4) add(b, a, 1);
		else if (o == 5) add(a, b, 0);
		else {
			add(a, b, 0);
			add(b, a, 0);
		}
	}
	for (int i = 1; i <= n; i++) add(0, i, 1);
	tarjan(0);
	for (int x = 0; x <= n; x++)
		for (unsigned int i = 0; i < e[x].size(); i++) {
			int y = e[x][i].first, z = e[x][i].second;
			if (c[x] == c[y]) {
				if (!z) continue;
				puts("-1");
				return 0;
			}
			addc(c[x], c[y], z);
		}
	for (int i = 1; i <= cnt; i++)
		if (!deg[i]) q.push(i);
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (unsigned int i = 0; i < ec[x].size(); i++) {
			int y = ec[x][i].first, z = ec[x][i].second;
			f[y] = max(f[y], f[x] + z);
			if (!--deg[y]) q.push(y);
		}
	}
	ll ans = 0;
	for (int i = 1; i <= cnt; i++) ans += (ll)f[i] * scc[i];
	cout << ans << endl;
	return 0;
}
