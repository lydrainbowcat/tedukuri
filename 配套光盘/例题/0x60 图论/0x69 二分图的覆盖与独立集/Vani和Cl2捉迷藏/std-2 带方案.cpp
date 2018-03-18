#define FILEIO

#define INPUT "travel.in"
#define OUTPUT "travel.out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 222;
	
	int n, m, c[MAXN][MAXN];

	inline void Input(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			c[x][y] = 1;
		}
		for (int i = 1; i <= n; i++) c[i][i] = 1;
	}

	int link[MAXN], vis[MAXN], cur, fim[MAXN];

	inline bool Dfs(int u) {
		for (int i = 1; i <= n; i++) if (c[u][i] && vis[i] != cur) {
			vis[i] = cur;
			if (!link[i] || Dfs(link[i])) {
				link[i] = u;
				return true;
			}
		}
		return false;
	}

	int End[MAXN], nE;

	inline void Work(void) {
		for (int k = 1; k <= n; k++) 
			for (int i = 1; i <= n; i++) 
				for (int j = 1; j <= n; j++) 
					c[i][j] |= c[i][k] && c[k][j];
		for (int i = 1; i <= n; i++) c[i][i] = 0;
		int Ans = n;
		for (int i = 1; i <= n; i++) {
			++cur;
			Ans -= Dfs(i);
		}
		for (int i = 1; i <= n; i++) fim[link[i]] = i;
		for (int i = 1; i <= n; i++) if (!fim[i]) {
			End[++nE] = i;
		}
		++cur;
		printf("%d\n", Ans);
		while (true) {
			bool modify = false;
			for (int i = 1; i <= nE; i++) 
				for (int j = 1; j <= n; j++) if (c[End[i]][j])
					vis[j] = cur;
			for (int i = 1; i <= nE; i++) if (vis[End[i]] == cur) {
				modify = true;
				while (vis[End[i]] == cur)
					End[i] = link[End[i]];
			}
			if (!modify) break;
		}
		for (int i = 1; i <= nE; i++) printf("%d ", End[i]);
	}

	inline void solve(void) {
		Input();
		Work();
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

