#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, m, t, ans, fx[105][105], fy[105][105];
bool a[105][105], v[105][105];
const int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool dfs(int x, int y) {
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 1 || ny < 1 || nx > n || ny > m || a[nx][ny]) continue;
		if (v[nx][ny]) continue;
		v[nx][ny] = 1;
		if (fx[nx][ny] == 0 || dfs(fx[nx][ny], fy[nx][ny])) {
			fx[nx][ny] = x, fy[nx][ny] = y;
			return true;
		}
	}
	return false;
}

int main() {
	cin >> n >> m >> t;
	for (int i = 1; i <= t; i++) {
		int x, y; cin >> x >> y;
		a[x][y] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i + j & 1) continue;
			if (a[i][j]) continue;
			memset(v, 0, sizeof(v));
			if (dfs(i, j)) ans++;
		}
	}
	cout << n * m - t - ans << endl;
}

