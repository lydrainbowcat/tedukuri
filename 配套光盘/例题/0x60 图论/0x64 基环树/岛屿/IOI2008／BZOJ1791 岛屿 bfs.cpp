//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1000006;
int Head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], tot;
int n, du[N], c[N], q[N<<1];
ll f[N], d[N], a[N<<1], b[N<<1], ans;
bool v[N];

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
	++du[y];
}

void bfs(int s, int t) {
	int l = 1, r = 1;
	c[q[1]=s] = t;
	while (l <= r) {
		for (int i = Head[q[l]]; i; i = Next[i])
			if (!c[Edge[i]]) c[q[++r]=Edge[i]] = t;
		++l;
	}
}

void topsort() {
	int l = 1, r = 0;
	for (int i = 1; i <= n; i++)
		if (du[i] == 1) q[++r] = i;
	while (l <= r) {
		for (int i = Head[q[l]]; i; i = Next[i])
			if (du[Edge[i]] > 1) {
				d[c[q[l]]] = max(d[c[q[l]]], f[q[l]] + f[Edge[i]] + Leng[i]);
				f[Edge[i]] = max(f[Edge[i]], f[q[l]] + Leng[i]);
				if (--du[Edge[i]] == 1) q[++r] = Edge[i];
			}
		++l;
	}
}

void dp(int t, int x) {
	int m = 0, y = x, k, z = 0;
	do {
		a[++m] = f[y];
		du[y] = 1;
		for (k = Head[y]; k; k = Next[k])
			if (du[Edge[k]] > 1) {
				b[m+1] = b[m] + Leng[k];
				y = Edge[k];
				break;
			}
	} while (k);
	if (m == 2) {
		for (int i = Head[y]; i; i = Next[i])
			if (Edge[i] == x) z = max(z, Leng[i]);
		d[t] = max(d[t], f[x] + f[y] + z);
		return;
	}
	for (int i = Head[y]; i; i = Next[i])
		if (Edge[i] == x) {
			b[m+1] = b[m] + Leng[i];
			break;
		}
	for (int i = 1; i < m; i++) {
		a[m+i] = a[i];
		b[m+i] = b[m+1] + b[i];
	}
	int l = 1, r = 1;
	q[1] = 1;
	for (int i = 2; i < (m << 1); i++) {
		if (l <= r && i - q[l] >= m) ++l;
		d[t] = max(d[t], a[i] + a[q[l]] + b[i] - b[q[l]]);
		while (l <= r && a[q[r]] - b[q[r]] <= a[i] - b[i]) --r;
		q[++r] = i;
	}
}

int main() {
	cin >> n;
	for (int x = 1; x <= n; x++) {
		int y, z;
		scanf("%d %d", &y, &z);
		add(x, y, z);
		add(y, x, z);
	}
	int t = 0;
	for (int i = 1; i <= n; i++)
		if (!c[i]) bfs(i, ++t);
	topsort();
	for (int i = 1; i <= n; i++)
		if (du[i] > 1 && !v[c[i]]) {
			v[c[i]] = 1;
			dp(c[i], i);
			ans += d[c[i]];
		}
	cout << ans << endl;
	return 0;
}
