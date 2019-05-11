//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 106;
int n, m, d[N][N];
ll c[N][N];
double ans[N];

int main() {
	memset(d, 0x3f, sizeof(d));
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		c[x][y] = c[y][x] = 1;
		d[x][y] = d[y][x] = z;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i != j && i != k && j != k) {
					if (d[i][j] > d[i][k] + d[k][j]) {
						d[i][j] = d[i][k] + d[k][j];
						c[i][j] = c[i][k] * c[k][j];
					} else if (d[i][j] == d[i][k] + d[k][j])
						c[i][j] += c[i][k] * c[k][j];
				}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i != j && i != k && j != k)
					if (d[i][k] + d[k][j] == d[i][j])
						ans[k] += (double)c[i][k] * c[k][j] / c[i][j];
	for (int i = 1; i <= n; i++) printf("%.3lf\n", ans[i]);
	return 0;
}
