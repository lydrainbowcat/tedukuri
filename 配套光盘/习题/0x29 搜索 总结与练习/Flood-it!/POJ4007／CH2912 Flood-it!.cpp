//Author:XuHt
#include <cstring>
#include <iostream>
using namespace std;
const int N = 10;
int n, a[N][N], dep, v[N][N];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

bool pd(int x, int y) {
	return x > 0 && x <= n && y > 0 && y <= n;
}

void dfs(int x, int y, int z) {
	v[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (!pd(nx, ny)) continue;
		if (v[nx][ny] == 1) continue;
		v[nx][ny] = 2;
		if (a[nx][ny] == z) dfs(nx, ny, z);
	}
}

int gj() {
	int ans = 0;
	bool w[6];
	memset(w, 0, sizeof(w));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (!w[a[i][j]] && v[i][j] != 1) {
				w[a[i][j]] = 1;
				++ans;
			}
	return ans;
}

bool dfs0(int now) {
	int cnt = gj();
	if (now + cnt > dep) return 0;
	if (!cnt) return 1;
	int w[N][N];
	memcpy(w, v, sizeof(w));
	for (int i = 0; i < 6; i++) {
		bool flag = 0;
		for (int x = 1; x <= n; x++)
			for (int y = 1; y <= n; y++)
				if (a[x][y] == i && v[x][y] == 2) {
					flag = 1;
					dfs(x, y, i);
				}
		if (flag && dfs0(now + 1)) return 1;
		memcpy(v, w, sizeof(v));
	}
	return 0;
}

int main() {
	while (cin >> n && n) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> a[i][j];
		memset(v, 0, sizeof(v));
		dfs(1, 1, a[1][1]);
		dep = 0;
		while (!dfs0(0)) ++dep;
		cout << dep << endl;
	}
	return 0;
}
