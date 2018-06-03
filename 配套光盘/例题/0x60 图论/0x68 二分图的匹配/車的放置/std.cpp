#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, m, t, ans, fa[205];
bool a[205][205], v[205];

bool dfs(int x) {
	for (int y = 1; y <= m; y++) {
		if (v[y] || a[x][y]) continue;
		v[y] = 1;
		if (fa[y] == 0 || dfs(fa[y])) {
			fa[y] = x;
			return true;
		}
	}
	return false;
}

int main() {
	cin >> n >> m >> t;
	for (int i = 1; i <= t; i++) {
		int x, y; cin >> x >> y;
		a[x][y] = 1;
	}
	for (int i = 1; i <= n; i++) {
		memset(v, 0, sizeof(v));
		if (dfs(i)) ans++;
	}
	cout << ans << endl;
}
