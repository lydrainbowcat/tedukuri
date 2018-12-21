//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10006;
int n, k, s[N], Ans;
bool v[N], w[N];
int Head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], t;
int ans, pos;
int d[N], b[N], a[N], tot, cnt[N];

void dfs_find(int S, int x) {
	v[x] = 1;
	s[x] = 1;
	int max_part = 0;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i];
		if (v[y] || w[y]) continue;
		dfs_find(S, y);
		s[x] += s[y];
		max_part = max(max_part, s[y]);
	}
	max_part = max(max_part, S - s[x]);
	if (max_part < ans) {
		ans = max_part;
		pos = x;
	}
}

void dfs(int x) {
	v[x] = 1;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i], z = Leng[i];
		if (v[y] || w[y]) continue;
		++cnt[b[a[++tot]=y]=b[x]];
		d[y] = d[x] + z;
		dfs(y);
	}
}

bool cmp(int i, int j) {
	return d[i] < d[j];
}

void work(int S, int x) {
	memset(v, 0, sizeof(v));
	ans = S;
	dfs_find(S, x);
	memset(d, 0, sizeof(d));
	memset(cnt, 0, sizeof(cnt));
	memset(v, 0, sizeof(v));
	w[a[tot=1]=b[pos]=pos] = 1;
	++cnt[pos];
	for (int i = Head[pos]; i; i = Next[i]) {
		int y = Edge[i], z = Leng[i];
		if (v[y] || w[y]) continue;
		++cnt[a[++tot]=b[y]=y];
		d[y] = z;
		dfs(y);
	}
	sort(a + 1, a + tot + 1, cmp);
	int l = 1, r = tot;
	--cnt[b[a[1]]];
	while (l < r) {
		while (d[a[l]] + d[a[r]] > k) --cnt[b[a[r--]]];
		Ans += r - l - cnt[b[a[l]]];
		--cnt[b[a[++l]]];
	}
	int now = pos;
	for (int i = Head[now]; i; i = Next[i]) {
		int y = Edge[i];
		if (w[y]) continue;
		work(s[y], y);
	}
}

void add(int x, int y, int z) {
	Edge[++t] = y;
	Leng[t] = z;
	Next[t] = Head[x];
	Head[x] = t;
}

void Tree() {
	t = 0;
	memset(Head, 0, sizeof(Head));
	for (int i = 1; i < n; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
	}
	memset(w, 0, sizeof(w));
	Ans = 0;
	work(n, 1);
	cout << Ans << endl;
}

int main() {
	while (cin >> n >> k && n && k) Tree();
	return 0;
}
