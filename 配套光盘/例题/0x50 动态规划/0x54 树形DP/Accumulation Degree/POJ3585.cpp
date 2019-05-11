#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int d[200010], v[200010], f[200010], deg[200010];
int head[200010], ver[400010], edge[400010], Next[400010];
int n, T, tot, root, ans;

void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}

void dp(int x) {
	v[x] = 1; // 访问标记
	d[x] = 0;
	for (int i = head[x]; i; i = Next[i]) { // 邻接表存储
		int y = ver[i];
		if (v[y]) continue;
		dp(y);
		if (deg[y] == 1) d[x] += edge[i]; // edge[i]保存c(x,y)
		else d[x] += min(d[y], edge[i]); 
	}
}

void dfs(int x) {
	v[x] = 1;
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (v[y]) continue;
		if (deg[x] == 1) f[y] = d[y] + edge[i];
		else f[y] = d[y] + min(f[x] - min(d[y], edge[i]), edge[i]);
		dfs(y);
	}
}

int main() {
	cin >> T;
	while (T--) {
		tot = 1;
		cin >> n;
		tot = 1;
		for (int i = 1; i <= n; i++)
			head[i] = f[i] = d[i] = deg[i] = v[i] = 0;
		for (int i = 1; i < n; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z), add(y, x, z);
			deg[x]++, deg[y]++;
		}
		int root = 1; // 任选一个点为源点
		dp(root);
		for (int i = 1; i <= n; i++) v[i] = 0;
		f[root] = d[root];
		dfs(root);
		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans = max(ans, f[i]);
		cout << ans << endl;
	}
}
