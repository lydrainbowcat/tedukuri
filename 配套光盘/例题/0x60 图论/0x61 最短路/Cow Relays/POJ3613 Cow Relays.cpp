//Author:XuHt
#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 206, INF = 0x3f3f3f3f;
int n, t, s, e, tot = 200;
map<int, int> m;
struct M {
	int a[N][N];
	void pre() {
		for (int i = 1; i <= tot; i++)
			for (int j = 1; j <= tot; j++)
				a[i][j] = INF;
	}
} st, ed;

M mul(M a, M b) {
	M c;
	c.pre();
	for (int i = 1; i <= tot; i++)
		for (int j = 1; j <= tot; j++)
			for (int k = 1; k <= tot; k++)
				c.a[i][j] = min(c.a[i][j], a.a[i][k] + b.a[k][j]);
	return c;
}

int main() {
	cin >> n >> t >> s >> e;
	st.pre();
	tot = 0;
	while (t--) {
		int x, y, z;
		scanf("%d %d %d", &z, &x, &y);
		x = m[x] ? m[x] : (m[x] = ++tot);
		y = m[y] ? m[y] : (m[y] = ++tot);
		st.a[x][y] = st.a[y][x] = z;
	}
	memcpy(ed.a, st.a, sizeof(ed.a));
	--n;
	while (n) {
		if (n & 1) ed = mul(ed, st);
		st = mul(st, st);
		n >>= 1;
	}
	cout << ed.a[m[s]][m[e]] << endl;
	return 0;
}
