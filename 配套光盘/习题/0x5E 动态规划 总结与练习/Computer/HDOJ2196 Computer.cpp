//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10006;
int n, f[N][3];
vector<pair<int, int> > e[N];

void dfs1(int fa, int x) {
	int ans[2] = {0,0};
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first, z = e[x][i].second;
		if (y == fa) continue;
		dfs1(x, y);
		int w = f[y][0] + z;
		if (w >= ans[0]) {
			ans[1] = ans[0];
			ans[0] = w;
		} else if (w > ans[1]) ans[1] = w;
	}
	f[x][0] = ans[0];
	f[x][1] = ans[1];
}

void dfs2(int fa, int x) {
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first, z = e[x][i].second;
		if (y == fa) continue;
		int w = f[y][0] + z == f[x][0] ? f[x][1] : f[x][0];
		f[y][2] = max(f[x][2], w) + z;
		dfs2(x, y);
	}
}

void Computer() {
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 2; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		e[i].push_back(make_pair(x, y));
		e[x].push_back(make_pair(i, y));
	}
	memset(f, 0, sizeof(f));
	dfs1(-1, 1);
	dfs2(-1, 1);
	for (int i = 1; i <= n; i++)
		printf("%d\n", max(f[i][0], f[i][2]));
}

int main() {
	while (cin >> n) Computer();
	return 0;
}
