//Author:XuHt
#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 206, INF = 0x3f3f3f3f, S = 106;
int n, m, a[N], f[N][N];
map<string, int> mp;
vector<int> e[N];
bool v[N];
char s[S];

int dfs(int x) {
	for (int i = 1; i <= n; i++) f[x][i] = INF;
	f[x][0] = 0;
	int cnt = 1;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		cnt += dfs(y);
		for (int j = n; j >= 0; j--)
			for (int k = 0; k <= j; k++)
				f[x][j] = min(f[x][j], f[x][j-k] + f[y][k]);
	}
	f[x][cnt] = min(f[x][cnt], a[x]);
	return cnt;
}

void Bribing_FIPA() {
	sscanf(s, "%d %d", &n, &m);
	int num = 0;
	mp.clear();
	memset(v, 1, sizeof(v));
	for (int i = 0; i <= n; i++) e[i].clear();
	for (int i = 1; i <= n; i++) {
		int d;
		scanf("%s %d", s, &d);
		if (mp.find(s) == mp.end()) mp[s] = ++num;
		int x = mp[s];
		a[x] = d;
		fgets(s, sizeof(s), stdin);
		stringstream ss(s);
		string str;
		while (ss >> str) {
			if (mp.find(str) == mp.end()) mp[str] = ++num;
			int y = mp[str];
			v[y] = 0;
			e[x].push_back(y);
		}
	}
	for (int i = 1; i <= n; i++) if (v[i]) e[0].push_back(i);
	a[0] = INF;
	dfs(0);
	int ans = INF;
	for (int i = m; i <= n; i++) ans = min(ans, f[0][i]);
	cout << ans << endl;
}

int main() {
	while (fgets(s, sizeof(s), stdin) && s[0] != '#') Bribing_FIPA();
	return 0;
}
