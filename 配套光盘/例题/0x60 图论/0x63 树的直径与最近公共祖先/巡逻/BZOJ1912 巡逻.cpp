//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006;
int n, k, d[N], fa[N];
int Head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], tot = 1;
bool v[N];

void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

void dfs(int x, int &t) {
	v[x] = 1;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i], z = Leng[i];
		if (v[y]) continue;
		if ((d[y] = d[x] + z) >= d[t]) t = y;
		fa[y] = i;
		dfs(y, t);
	}
	v[x] = 0;
}

void dp(int x, int &t) {
	v[x] = 1;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i], z = Leng[i];
		if (v[y]) continue;
		dp(y, t);
		t = max(t, d[x] + d[y] + z);
		d[x] = max(d[x], d[y] + z);
	}
}

int main() {
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		add(x, y, 1);
		add(y, x, 1);
	}
	int t = 1;
	dfs(1, t);
	d[t] = fa[t] = 0;
	int tt = t;
	dfs(t, tt);
	int ans = ((n - 1) << 1) - d[tt] + 1;
	if (k == 2) {
		while (fa[tt]) {
			Leng[fa[tt]] = Leng[fa[tt]^1] = -1;
			tt = Edge[fa[tt]^1];
		}
		tt = 0;
		memset(d, 0, sizeof(d));
		dp(t, tt);
		ans -= tt - 1;
	}
	cout << ans << endl;
	return 0;
}
