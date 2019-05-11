//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 56;
int n, m, a[N][N], f[N<<1][N][N];

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for (int i = 0; i < n + m - 2; i++)
		for (int j = 1; j <= n && j <= i + 1; j++)
			for (int k = 1; k <= n && k <= i + 1; k++) {
				if (j == k) {
					f[i+1][j][k] = max(f[i+1][j][k], f[i][j][k] + a[j][i+3-j]);
					f[i+1][j+1][k+1] = max(f[i+1][j+1][k+1], f[i][j][k] + a[j+1][i+2-j]);
				} else {
					f[i+1][j][k] = max(f[i+1][j][k], f[i][j][k] + a[j][i+3-j] + a[k][i+3-k]);
					f[i+1][j+1][k+1] = max(f[i+1][j+1][k+1], f[i][j][k] + a[j+1][i+2-j] + a[k+1][i+2-k]);
				}
				if (j + 1 == k) f[i+1][j+1][k] = max(f[i+1][j+1][k], f[i][j][k] + a[j+1][i+2-j]);
				else f[i+1][j+1][k] = max(f[i+1][j+1][k], f[i][j][k] + a[j+1][i+2-j] + a[k][i+3-k]);
				if (k + 1 == j) f[i+1][j][k+1] = max(f[i+1][j][k+1], f[i][j][k] + a[j][i+3-j]);
				else f[i+1][j][k+1] = max(f[i+1][j][k+1], f[i][j][k] + a[j][i+3-j] + a[k+1][i+2-k]);
			}
	cout << f[n+m-2][n][n] << endl;
	return 0;
}
