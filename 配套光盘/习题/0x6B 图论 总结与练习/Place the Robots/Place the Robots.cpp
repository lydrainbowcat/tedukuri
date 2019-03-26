//Author:xht37
#include <cstdio>
#include <bitset>
#include <vector>
#include <iostream>
using namespace std;
const int N = 56;
int n, m, fa[N][N], fb[N][N], f[N*N], id;
char s[N][N];
vector<int> e[N*N];
bitset<N*N> v;

inline void add(int x, int y) {
	e[x].push_back(y);
}

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

inline void Place_the_Robots() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	int a = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] != '#')
				fa[i][j] = a += j == 1 || s[i][j-1] == '#';
	int b = a;
	for (int j = 1; j <= m; j++)
		for (int i = 1; i <= n; i++)
			if (s[i][j] != '#')
				fb[i][j] = b += i == 1 || s[i-1][j] == '#';
	for (int i = 1; i <= b; i++) {
		e[i].clear();
		f[i] = 0;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] == 'o') {
				add(fa[i][j], fb[i][j]);
				add(fb[i][j], fa[i][j]);
			}
	int ans = 0;
	for (int i = 1; i <= a; i++) {
		v <<= b;
		ans += dfs(i);
	}
	cout << "Case :"  << ++id << endl << ans << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) Place_the_Robots();
	return 0;
}
