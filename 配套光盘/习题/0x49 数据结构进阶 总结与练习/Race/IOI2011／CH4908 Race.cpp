//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006;
int n, k, ans, pos, s[N], Ans;
int Head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], t = 0;
bool v[N];
int a[N], b[N], c[N], d[N], tot;

void dfs_find(int S, int x) {
	v[x] = 1;
	s[x] = 1;
	int max_part = 0;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i];
		if (v[y]) continue;
		dfs_find(S, y);
		s[x] += s[y];
		max_part = max(max_part, s[y]);
	}
	max_part = max(max_part, S - s[x]);
	if (max_part < ans) {
		ans = max_part;
		pos = x;
	}
	v[x] = 0;
}

void dfs(int x) {
	v[x] = 1;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i], z = Leng[i];
		if (v[y]) continue;
		b[a[++tot]=y] = b[x];
		c[y] = c[x] + 1;
		d[y] = d[x] + z;
		dfs(y);
	}
	v[x] = 0;
}

inline bool cmp(int i, int j) {
	return d[i] < d[j] || (d[i] == d[j] && c[i] < c[j]);
}

void work(int S, int x) {
	ans = S;
	dfs_find(S, x);
	d[x] = 0;
	v[a[tot=1]=b[pos]=pos] = 1;
	for (int i = Head[pos]; i; i = Next[i]) {
		int y = Edge[i], z = Leng[i];
		if (v[y]) continue;
		c[a[++tot]=b[y]=y] = 1;
		d[y] = z;
		dfs(y);
	}
	sort(a + 1, a + tot + 1, cmp);
	int l = 1, r = tot;
	while (l < r) {
		while (l < r && d[a[l]] + d[a[r]] > k) r--;
		while (l < r && d[a[l]] + d[a[r]] == k) {
			if (b[a[l]] != b[a[r]])
				Ans = min(Ans, c[a[l]] + c[a[r]]);
			r--;
		}
		l++;
	}
	int now = pos;
	for (int i = Head[now]; i; i = Next[i]) {
		int y = Edge[i];
		if (v[y]) continue;
		work(s[y], y);
	}
}

inline void add(int x, int y, int z) {
	Edge[++t] = y;
	Leng[t] = z;
	Next[t] = Head[x];
	Head[x] = t;
}

int main() {
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(++x, ++y, z);
		add(y, x, z);
	}
	memset(v, 0, sizeof(v));
	Ans = n;
	work(n, 1);
	if (Ans == n) puts("-1");
	else cout << Ans << endl;
	return 0;
}
