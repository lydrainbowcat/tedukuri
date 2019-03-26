//Author:xht37
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#define x first
#define y second
using namespace std;
const int N = 206;
int n, a[N], c[N], num[2], cnt, f[N][N<<1], g[N][N<<1];
pair<int, int> p[N];
vector<int> e[N], d[N][2], ans[2];

bool dfs(int x, int color) {
	c[x] = color;
	num[color]++;
	d[cnt][color].push_back(x);
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (c[y] == -1) {
			if (!dfs(y, color ^ 1)) return 0;
		} else if (c[y] == color) return 0;
	}
	return 1;
}

void print(int k, int x) {
	if (!k) return;
	int t = g[k][x];
	for (int i = 0; i < 2; i++)
		for (unsigned int j = 0; j < d[k][i].size(); j++)
			ans[i^t].push_back(d[k][i][j]);
	print(k - 1, x + d[k][t].size() - d[k][t^1].size());
}

int main() {
	cin >> n;
	memset(c, -1, sizeof(c));
	for (int i = 1; i <= n; i++) {
		int x;
		memset(a, 0, sizeof(a));
		while (scanf("%d", &x) && x) a[x] = 1;
		for (int j = 1; j <= n; j++)
			if (!a[j] && i != j) {
				e[i].push_back(j);
				e[j].push_back(i);
			}
	}
	for (int i = 1; i <= n; i++)
		if (c[i] == -1) {
			num[0] = num[1] = 0;
			++cnt;
			if (!dfs(i, 0)) {
				puts("No solution");
				return 0;
			}
			p[cnt] = make_pair(num[0], num[1]);
		}
	f[0][100] = 1;
	for (int i = 1; i <= cnt; i++)
		for (int j = 0; j <= 200; j++)
			if (f[i-1][j]) {
				int x = p[i].x, y = p[i].y;
				f[i][j+x-y] = 1;
				f[i][j+y-x] = 1;
				g[i][j+x-y] = 1;
				g[i][j+y-x] = 0;
			}
	for (int i = 0; i <= 100; i++)
		if (f[cnt][100-i]) {
			print(cnt, i + 100);
			break;
		}
	cout << ans[0].size() << " ";
	for (unsigned int i = 0; i < ans[0].size(); i++)
		printf("%d ", ans[0][i]);
	cout << endl << ans[1].size() << " ";
	for (unsigned int i = 0; i < ans[1].size(); i++)
		printf("%d ", ans[1][i]);
	cout << endl;
	return 0;
}
