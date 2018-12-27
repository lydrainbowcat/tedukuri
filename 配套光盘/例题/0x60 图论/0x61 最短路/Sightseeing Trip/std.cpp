#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int a[310][310], d[310][310], pos[310][310];
int n, m, ans = 0x3f3f3f3f;
vector<int> path; //具体方案
void get_path(int x, int y) {
	if (pos[x][y] == 0) return;
	get_path(x, pos[x][y]);
	path.push_back(pos[x][y]);
	get_path(pos[x][y], y);
}
int main() {
	cin >> n >> m;
	memset(a, 0x3f, sizeof(a));
	for (int i = 1; i <= n; i++) a[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		a[y][x] = a[x][y] = min(a[x][y], z);
	}
	memcpy(d, a, sizeof(a));
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i < k; i++)
			for (int j = i + 1; j < k; j++)
				if ((long long)d[i][j] + a[j][k] + a[k][i] < ans) {
					ans = d[i][j] + a[j][k] + a[k][i];
					path.clear();
					path.push_back(i);
					get_path(i, j);
					path.push_back(j);
					path.push_back(k);
				}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
					pos[i][j] = k;
				}
	}
	if (ans == 0x3f3f3f3f) {
		puts("No solution.");
		return 0;
	}
	for (int i = 0; i < path.size(); i++)
		printf("%d ", path[i]);
	puts("");
}
