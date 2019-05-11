//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 106;
int n, m, k, f[N], ans;
bool v[N];
vector<int> e[N];

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

inline void Machine_Schedule() {
	cin >> m >> k;
	for (int i = 1; i < n; i++) e[i].clear();
	for (int i = 0; i < k; i++) {
		int x, y;
		scanf("%d %d %d", &i, &x, &y);
		if (x && y) e[x].push_back(y);
	}
	memset(f, 0, sizeof(f));
	ans = 0;
	for (int i = 1; i < n; i++) {
		memset(v, 0, sizeof(v));
		ans += dfs(i);
	}
	cout << ans << endl;
}

int main() {
	while (cin >> n && n) Machine_Schedule();
	return 0;
}
