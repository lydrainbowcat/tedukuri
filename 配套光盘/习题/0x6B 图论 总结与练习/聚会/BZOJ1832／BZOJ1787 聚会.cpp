//Author:XuHt
#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 500006;
int n, m, t, f[N][20], d[N];
bool v[N];
queue<int> q;
vector<int> e[N];

void bfs() {
	q.push(1);
	v[1] = 1;
	d[1] = 1;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (unsigned int i = 0; i < e[x].size(); i++) {
			int y = e[x][i];
			if (v[y]) continue;
			q.push(y);
			v[y] = 1;
			d[y] = d[x] + 1;
			f[y][0] = x;
			for (int j = 1; j <= t; j++)
				f[y][j] = f[f[y][j-1]][j-1];
		}
	}
}

int lca(int x, int y) {
	if (d[x] > d[y]) swap(x, y);
	for (int i = t; i >= 0; i--)
		if (d[f[y][i]] >= d[x]) y = f[y][i];
	if (x == y) return x;
	for (int i = t; i >= 0; i--)
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	return f[x][0];
}

int main() {
	cin >> n >> m;
	t = log(n) / log(2);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	bfs();
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		int xy = lca(x, y), yz = lca(y, z), xz = lca(x, z);
		int s = d[x] + d[y] - (d[xy] << 1);
		if (d[xy] < d[yz]) {
			xy = yz;
			s = d[y] + d[z] - (d[yz] << 1);
			z = x;
		}
		if (d[xy] < d[xz]) {
			xy = xz;
			s = d[x] + d[z] - (d[xz] << 1);
			z = y;
		}
		s += d[z] + d[xy] - (d[lca(z,xy)] << 1);
		printf("%d %d\n", xy, s);
	}
	return 0;
}
