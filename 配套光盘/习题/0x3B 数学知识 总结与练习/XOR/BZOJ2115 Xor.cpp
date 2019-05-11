//Author:XuHt
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 50006;
int n, m, tot = 0;
vector<pair<int, ll> > e[N];
queue<int> q;
bool v[N];
ll d[N], a[N*6], f[66];

void dfs(int x) {
	v[x] = 1;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first;
		ll z = e[x][i].second;
		if (v[y]) a[++tot] = d[x] ^ d[y] ^ z;
		else {
			d[y] = d[x] ^ z;
			dfs(y);
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		ll z;
		scanf("%d %d %lld", &x, &y, &z);
		e[x].push_back(make_pair(y, z));
		e[y].push_back(make_pair(x, z));
	}
	memset(v, 0, sizeof(v));
	d[1] = 0;
	dfs(1);
	memset(f, 0, sizeof(0));
	for (int i = 1; i <= tot; i++)
		for (int j = 60; j >= 0; j--)
			if ((a[i] >> j) & 1) {
				if (!f[j]) {
					f[j] = a[i];
					break;
				}
				a[i] ^= f[j];
			}
	ll ans = d[n];
	for (int i = 60; i >= 0; i--)
		if (!((ans >> i) & 1)) ans ^= f[i];
	cout << ans << endl;
	return 0;
}
