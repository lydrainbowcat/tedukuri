//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106;
int n, m, f[N][N];

int main() {
	cin >> n >> m;
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; i++) f[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		f[x][y] = f[y][x] = 1;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			ans = max(ans, f[i][j]);
	cout << ans << endl;
	return 0;
}
