//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 206;
int a[N];
double p[N], f[N][N][N<<1];

int main() {
	int n, l, t;
	cin >> n >> l >> t;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		p[i] /= 100;
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	if (t > n) t = n;
	f[0][0][t+200] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= n; j++)
			for (int k = -n; k <= n; k++)
				if (a[i+1] == -1) {
					f[i+1][j][k+200] += f[i][j][k+200] * (1 - p[i+1]);
					f[i+1][j+1][k-1+200] += f[i][j][k+200] * p[i+1];
				} else {
					f[i+1][j+1][min(k+a[i+1],n)+200] += f[i][j][k+200] * p[i+1];
					f[i+1][j][k+200] += f[i][j][k+200] * (1 - p[i+1]);
				}
	double ans = 0;
	for (int j = l; j <= n; j++)
		for (int k = 0; k <= n; k++)
			ans += f[n][j][k+200];
	printf("%.6f\n", ans);
	return 0;
}
