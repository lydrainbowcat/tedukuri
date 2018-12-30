//Author:XuHt
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1006;
int n, m, x, y;
double f[N][N], d[N][N];

void work() {
	for (int i = 1; i <= m; i++) {
		double w = 1.0 / d[i][i];
		d[i][i] *= w;
		d[i][m+1] *= w;
		if (i == m) break;
		d[i][i+1] *= w;
		w = d[i+1][i] / d[i][i];
		d[i+1][i] -= w * d[i][i];
		d[i+1][i+1] -= w * d[i][i+1];
		d[i+1][m+1] -= w * d[i][m+1];
	}
	for (int i = m - 1; i; i--)
		d[i][m+1] -= d[i+1][m+1] * d[i][i+1];
}

int main() {
	cin >> n >> m >> x >> y;
	for (int i = n - 1; i >= x; i--) {
		d[1][1] = d[m][m] = -2 / 3.0;
		d[1][2] = d[m][m-1] = 1 / 3.0;
		for (int j = 2; j < m; j++) {
			d[j][m+1] = -f[i+1][j] / 4.0 - 1;
			d[j][j] = -3 / 4.0;
			d[j][j-1] = d[j][j+1] = 1 / 4.0;
		}
		if (m == 1) d[1][1] = -1 / 2.0;
		d[1][m+1] = -f[i+1][1] / 3.0 - 1;
		d[m][m+1] = -f[i+1][m] / 3.0 - 1;
		if (m == 1) d[m][m+1] = -f[i+1][m] / 2.0 - 1;
		work();
		for (int j = 1; j <= m; j++) f[i][j] = d[j][m+1];
	}
	printf("%.10f\n", f[x][y]);
	return 0;
}
