//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 356, M = 126, S = 46; 
int n, m, a[N], c[5], f[M][S][S][S];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) {
		int t;
		scanf("%d", &t);
		++c[t];
	}
	for (int i = 1; i <= m; i++)
		for (int x = 0; x <= c[1] && x <= m; x++)
			for (int y = 0; y <= c[2] && y <= m - x; y++)
				for (int z = 0; z <= c[3] && z <= m - x - y; z++) {
					int w = x + 2 * y + 3 * z + 4 * (i - x - y - z) + 1;
					if (i - x - y - z) f[i][x][y][z] = f[i-1][x][y][z];
					if (x) f[i][x][y][z] = max(f[i][x][y][z], f[i-1][x-1][y][z]);
					if (y) f[i][x][y][z] = max(f[i][x][y][z], f[i-1][x][y-1][z]);
					if (z) f[i][x][y][z] = max(f[i][x][y][z], f[i-1][x][y][z-1]);
					f[i][x][y][z] += a[w];
				}
	cout << f[m][c[1]][c[2]][c[3]] + a[1] << endl;
	return 0;
}
