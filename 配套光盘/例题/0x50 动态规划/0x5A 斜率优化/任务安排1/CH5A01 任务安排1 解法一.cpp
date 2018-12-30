//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 5006;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n;
ll s, st[N], sc[N], f[N][N];

int main() {
	cin >> n >> s;
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &st[i], &sc[i]);
		st[i] += st[i-1];
		sc[i] += sc[i-1];
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			for (int k = 0; k < i; k++)
				f[i][j] = min(f[i][j], f[k][j-1] + (s * j + st[i]) * (sc[i] - sc[k]));
	ll ans = INF;
	for (int i = 1; i <= n; i++)
		ans = min(ans, f[n][i]);
	cout << ans << endl;
	return 0;
}
