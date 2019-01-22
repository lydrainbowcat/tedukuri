//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 106;
const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};
int n, m, ans, f[N*N];
bool b[N][N], v[N*N];
vector<int> e[N*N];

bool dfs(int x) {
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (v[y]) continue;
		v[y] = 1;
		if (f[y] == -1 || dfs(f[y])) {
			f[y] = x;
			return 1;
		}
	}
	return 0;
}

int main() {
	cin >> n >> m;
	while (m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		b[x-1][y-1] = 1;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!b[i][j])
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k], y = j + dy[k];
					if (x >= 0 && x < n && y >= 0 && y < n && !b[x][y]) {
						e[i*n+j].push_back(x * n + y);
						e[x*n+y].push_back(i * n + j);
					}
				}
	memset(f, -1, sizeof(f));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if ((i ^ j) & 1) continue;
			memset(v, 0, sizeof(v));
			ans += dfs(i * n + j);
		}
	cout << ans << endl;
	return 0;
}
