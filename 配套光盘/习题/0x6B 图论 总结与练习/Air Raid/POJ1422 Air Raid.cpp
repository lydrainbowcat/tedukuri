//Author:xht37
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 306;
int n, m, f[N];
vector<int> e[N];
bitset<N> v;

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

inline void Air_Raid() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		e[x].push_back(y + n);
		e[y+n].push_back(x);
	}
	memset(f, 0, sizeof(f));
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		v.reset();
		ans += dfs(i);
	}
	cout << n - ans << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) Air_Raid();
	return 0;
}
