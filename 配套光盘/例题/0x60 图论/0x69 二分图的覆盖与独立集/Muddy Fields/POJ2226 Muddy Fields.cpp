//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 56;
int n, m, tot = 1, a[N][N][2], f[N*N], ans;
char s[N][N];
bool v[N*N];
vector<int> e[N*N];

bool dfs(int x) {
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (v[y]) continue;
		v[y] = 1;
		if (!f[y] || dfs(f[y])) {
			f[y] = x;
			return 1;
		}
	}
	return 0;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m + 1; j++)
			if (s[i][j] == '*') a[i][j][0] = tot;
			else ++tot;
	int t = tot;
	for (int j = 1; j <= m; j++)
		for (int i = 1; i <= n + 1; i++)
			if (s[i][j] == '*') a[i][j][1] = tot;
			else ++tot;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] == '*') {
				e[a[i][j][0]].push_back(a[i][j][1]);
				e[a[i][j][1]].push_back(a[i][j][0]);
			}
	for (int i = 1; i < t; i++) {
		memset(v, 0, sizeof(v));
		ans += dfs(i);
	}
	cout << ans << endl;
	return 0;
}
