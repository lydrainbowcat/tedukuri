#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long f[51][51], g[51][51][51], h[51], c[51][51], pow2[1250];
int n, m, mod = 1000000007;

int main() {
	// cin >> n >> m;
	// if (m >= n) {
	// 	cout << 0 << endl;
	// 	return 0;
	// }
	cin >> n;
	for (int i = 0; i <= n; i++) c[i][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	pow2[0] = 1;
	for (int i = 1; i <= n * (n - 1) / 2; i++)
		pow2[i] = pow2[i - 1] * 2 % mod;
	g[0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		h[i] = pow2[i*(i - 1) / 2];
		for (int j = 1; j < i; j++)
			h[i] = (h[i] - h[j] * c[i - 1][j - 1] % mod * pow2[(i - j)*(i - j - 1) / 2]) % mod;
		f[i][0] = h[i];
		for (int j = 1; j < i; j++) {
			for (int k = 1; k < i; k++) {
				long long component_1 = f[k][0] * c[i - 1][k - 1] % mod;
				long long k_x = 1;
				for (int x = 1; x <= min(i - k, j); x++) {
					k_x = k_x * k % mod;
					f[i][j] = (f[i][j] + component_1 * g[i - k][j - x][x] % mod * k_x) % mod;
				}
			}
			f[i][0] = (f[i][0] - f[i][j]) % mod;
		}
		for (int j = 0; j < i; j++)
			for (int k = 1; k <= i; k++)
				for (int p = 1; p <= i; p++)
					for (int q = 0; q <= j; q++)
						g[i][j][k] = (g[i][j][k] + f[p][q] * c[i - 1][p - 1] % mod * p % mod * g[i - p][j - q][k - 1]) % mod;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < n; j++)
			if (f[i][j]) cout << i << ' ' << j << ' ' << (f[i][j] + mod) % mod << endl;
	// cout << (f[n][m] + mod) % mod << endl;
}
