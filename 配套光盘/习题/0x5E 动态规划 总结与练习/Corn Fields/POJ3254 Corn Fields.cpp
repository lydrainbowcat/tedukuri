//Author:XuHt
#include <cstdio>
#include <iostream>
using namespace std;
const int P = 100000000;
int m, n, a, x[13], f[13][1<<12], M, ans = 0;
bool v[1<<12];

int main() {
	cin >> m >> n;
	M = (1 << n);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			cin >> a;
			(x[i] <<= 1) += a;
		}
	for (int i = 0; i < M; i++) v[i] = !(i & (i << 1)) && !(i & (i >> 1));
	f[0][0] = 1;
	for (int i = 1; i <= m; i++)
		for (int j = 0; j < M; j++)
			if (v[j] && ((j & x[i]) == j))
				for (int k = 0; k < M; k++)
					if (!(k & j)) f[i][j] = (f[i][j] + f[i-1][k]) % P;
	for (int i = 0; i < M; i++) (ans += f[m][i]) %= P;
	cout << ans << endl;
	return 0;
}
