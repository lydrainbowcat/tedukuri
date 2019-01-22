//Author:XuHt
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1006;
const ll P = (1ll << 31) - 1;
int n, m, a[N][N], d[N];
bool v[N];

int main() {
	cin >> n >> m;
	memset(a, 0x3f, sizeof(a));
	for (int i = 1; i <= n; i++) a[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		a[x][y] = a[y][x] = min(a[x][y], z);
	}
	memset(d, 0x3f, sizeof(d));
	d[1] = 0;
	for (int i = 1; i < n; i++) {
		int t = 0;
		for (int j = 1; j <= n; j++)
			if (!v[j] && (!t || d[j] < d[t])) t = j;
		v[t] = 1;
		for (int j = 1; j <= n; j++)
			d[j] = min(d[j], d[t] + a[t][j]);
	}
	memset(v, 0, sizeof(v));
	v[1] = 1;
	ll ans = 1;
	for (int i = 1; i < n; i++) {
		int t = 0, k = 0;
		for (int j = 2; j <= n; j++)
			if (!v[j] && (!t || d[j] < d[t])) t = j;
		for (int j = 1; j <= n; j++)
			if (v[j] && d[j] + a[j][t] == d[t]) ++k;
		v[t] = 1;
		(ans *= k) %= P;
	}
	cout << ans << endl;
	return 0;
}
