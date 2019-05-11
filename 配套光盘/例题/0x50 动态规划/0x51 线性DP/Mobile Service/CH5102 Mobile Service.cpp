//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int L = 206, N = 1006, INF = 0x3f3f3f3f;
int l, n, c[L][L], p[N], f[N][L][L];

int main() {
	memset(f, 0x3f, sizeof(f));
	cin >> l >> n;
	for (int i = 1; i <= l; i++)
		for (int j = 1; j <= l; j++)
			scanf("%d", &c[i][j]);
	p[0] = 3;
	f[0][1][2] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
		for (int j = 1; j <= l; j++)
			for (int k = 1; k <= l; k++)
				if (f[i-1][j][k] != INF) {
					if (j != p[i] && k != p[i])
						f[i][j][k] = min(f[i][j][k], f[i-1][j][k] + c[p[i-1]][p[i]]);
					if (j != p[i] && p[i-1] != p[i])
						f[i][j][p[i-1]] = min(f[i][j][p[i-1]], f[i-1][j][k] + c[k][p[i]]);
					if (k != p[i] && p[i-1] != p[i])
						f[i][p[i-1]][k] = min(f[i][p[i-1]][k], f[i-1][j][k] + c[j][p[i]]);
				}
	}
	int ans = INF;
	for (int i = 1; i <= l; i++)
		for (int j = 1; j <= l; j++)
			ans = min(ans, f[n][i][j]);
	cout << ans << endl;
	return 0;
}
