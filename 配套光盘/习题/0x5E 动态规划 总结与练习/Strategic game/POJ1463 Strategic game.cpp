//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1506, INF = 0x3f3f3f3f;
int n, f[N][2];
bool w[N];
vector<int> e[N];

void dfs(int u) {
	w[u] = 1;
	f[u][0] = 0;
	f[u][1] = 1;
	for (unsigned int i = 0; i < e[u].size(); i++) {
		int v = e[u][i];
		if (w[v]) continue;
		dfs(v);
		f[u][0] += f[v][1];
		f[u][1] += min(f[v][0], f[v][1]);
	}
}

void Strategic_game() {
	for (int i = 0; i < n; i++) e[i].clear();
	for (int i = 0; i < n; i++) {
		int u, k, v;
		scanf("%d:(%d)", &u, &k);
		while (k--) {
			scanf("%d", &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
	}
	int ans = 0;
	memset(w, 0, sizeof(w));
	for (int i = 0; i < n; i++) {
		if (w[i]) continue;
		dfs(i);
		ans += min(f[i][0], f[i][1]);
	}
	cout << ans << endl;
}

int main() {
	while (cin >> n) Strategic_game();
	return 0;
}
