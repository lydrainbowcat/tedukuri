//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 200006;
int n, m;
ll d[N], f[N];
bool v[N];
vector<pair<int, int> > e[N];

void dfs(int x, int &o) {
	v[x] = 1;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first, z = e[x][i].second;
		if (v[y]) continue;
		d[y] = d[x] + z;
		dfs(y, o);
	}
	v[x] = 0;
	if (d[x] > d[o]) o = x;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		e[x].push_back(make_pair(y, z));
		e[y].push_back(make_pair(x, z));
	}
	int s = 1;
	dfs(1, s);
	int t = s;
	d[s] = 0;
	dfs(s, t);
	memcpy(f, d, sizeof(f));
	d[t] = 0;
	dfs(t, s);
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, min(d[i], f[i]));
	cout << ans + f[t] << endl;
	return 0;
}
