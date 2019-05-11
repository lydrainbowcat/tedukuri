//Author:XuHt
#include <cstdio>
#include <vector>
#include <iostream>
#define ll long long
using namespace std;
const int N = 200006;
int n, p[N], q[N];
bool v[N];
ll d[N], f[N];
vector<pair<int, ll> > e[N];

void dfs(int x, int &o) {
	v[x] = 1;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first, z = e[x][i].second;
		if (v[y]) continue;
		d[y] = d[x] + z;
		p[y] = x;
		dfs(y, o);
	}
	v[x] = 0;
	if (d[x] > d[o]) o = x;
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		e[x].push_back(make_pair(y, z));
		e[y].push_back(make_pair(x, z));
	}
	int s = 1;
	dfs(1, s);
	int t = s;
	d[s] = p[s] = 0;
	dfs(s, t);
	cout << d[t] << endl;
	for (int i = t; i; i = p[i]) {
		v[i] = 1;
		q[p[i]] = i;
	}
	for (int x = t; x; x = p[x]) {
		f[x] = 0;
	 	for (unsigned int i = 0; i < e[x].size(); i++) {
			int y = e[x][i].first, z = e[x][i].second;
			if (v[y]) continue;
			d[y] = z;
			int w = y;
			dfs(y, w);
			f[x] = d[w];
		}
	}
	int i, ans = 0;
	for (i = s; i; i = q[i])
		if (d[t] - d[i] == f[i]) break;
	while (i) {
		if (d[i] == f[i]) break;
		++ans;
		i = p[i];
	}
	cout << ans << endl;
	return 0;
}
