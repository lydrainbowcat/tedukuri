//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 206;
ll a[N], f[N][N];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);;
	for (int i = n + 1; i <= n << 1; i++) a[i] = a[i-n];
	for (int len = 3; len <= n + 1; len++)
		for (int l = 1; l + len - 1 <= n << 1; l++) {
			int r = l + len - 1;
			for (int k = l + 1; k < r; k++)
				f[l][r] = max(f[l][r], f[l][k] + f[k][r] + a[l] * a[k] * a[r]);
		}
	ll ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, f[i][i+n]);
	cout << ans << endl;
	return 0;
}
