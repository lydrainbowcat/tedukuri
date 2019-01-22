//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000006, INF = 0x3f3f3f3f;
int n, fa[N], t, k, f[N][2], s[N][2], ans;
int Head[N], Edge[N<<1], Next[N<<1], tot;

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

inline void add(int x, int y) {
	Edge[++tot] = y;
	Next[tot] = Head[x];
	Head[x] = tot;
}

void dfs(int x) {
	int num = INF;
	f[x][0] = 0;
	for (int i = Head[x]; i; i = Next[i]) {
		if (Edge[i] != k) dfs(Edge[i]);
		f[x][0] += max(f[Edge[i]][0], f[Edge[i]][1]);
		num = min(num, max(f[Edge[i]][0], f[Edge[i]][1]) - f[Edge[i]][0]);
	}
	f[x][1] = f[x][0] + 1 - num;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		int p = get(x), q = get(i);
		if (p == q) {
			s[++t][0] = x;
			s[t][1] = i;
		} else {
			add(x, i);
			fa[q] = p;
		}
	}
	for (int i = 1; i <= t; i++) {
		k = 0;
		dfs(s[i][0]);
		k = s[i][0];
		dfs(s[i][1]);
		int now = f[s[i][1]][1];
		f[s[i][0]][1] = f[s[i][0]][0] + 1;
		dfs(s[i][1]);
		ans += max(now, f[s[i][1]][0]);
	}
	cout << ans << endl;
	return 0;
}
