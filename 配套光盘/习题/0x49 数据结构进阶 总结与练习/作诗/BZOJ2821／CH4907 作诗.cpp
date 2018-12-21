//Author:XuHt
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006, T = 2006;
int a[N], b[N], c[N], L[N], R[N], pos[N], f[T][T];
vector<int> e[N];
bool v[N];

inline bool pd(int x) {
	return x && !(x & 1);
}

inline int find(int x, int l, int r) {
	return upper_bound(e[x].begin(), e[x].end(), r) - lower_bound(e[x].begin(), e[x].end(), l);
}

int ask(int l, int r) {
	int p = pos[l], q = pos[r], cnt = 0;
	memset(v, 0, sizeof(v));
	if (p == q) {
		for (int i = l; i <= r; i++) {
			if (v[a[i]]) continue;
			v[a[i]] = 1;
			int w = find(a[i], l, r);
			if (pd(w)) ++cnt;
		}
		return cnt;
	}
	int x = 0, y = 0;
	if (p + 1 <= q - 1) {
		x = p + 1;
		y = q - 1;
	}
	cnt = f[x][y];
	for (int i = l; i <= R[p]; i++) {
		if (v[a[i]]) continue;
		v[a[i]] = 1;
		int c1 = find(a[i], l, r), c2 = find(a[i], L[x], R[y]);
		if (!pd(c1) && pd(c2)) --cnt;
		else if (pd(c1) && !pd(c2)) ++cnt;
	}
	for (int i = L[q]; i <= r; i++) {
		if (v[a[i]]) continue;
		v[a[i]] = 1;
		int c1 = find(a[i], l, r), c2 = find(a[i], L[x], R[y]);
		if (!pd(c1) && pd(c2)) --cnt;
		else if (pd(c1) && !pd(c2)) ++cnt;
	}
	return cnt;
}

int main() {
	int n, cc, m;
	cin >> n >> cc >> m;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	memcpy(b, a, sizeof(b));
	sort(b + 1, b + n + 1);
	int tot = unique(b + 1, b + n + 1) - (b + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
		e[a[i]].push_back(i);
	}
	int t = sqrt(log(n) / log(2) * n);
	int len = t ? n / t : n;
	for (int i = 1; i <= t; i++) {
		L[i] = (i - 1) * len + 1;
		R[i] = i * len;
	}
	if (R[t] < n) {
		L[t+1] = R[t] + 1;
		R[++t] = n;
	}
	for (int i = 1; i <= t; i++)
		for (int j = L[i]; j <= R[i]; j++)
			pos[j] = i;
	memset(f, 0, sizeof(f));
	for (int i = 1; i <= t; i++) {
		memset(c, 0, sizeof(c));
		int cnt = 0;
		for (int j = L[i]; j <= n; j++) {
			if (++c[a[j]] > 1) {
				if (c[a[j]] & 1) --cnt;
				else ++cnt;
			}
			f[i][pos[j]] = cnt;
		}
	}
	int x = 0;
	while (m--) {
		int l, r;
		scanf("%d %d", &l, &r);
		l = (l + x) % n + 1;
		r = (r + x) % n + 1;
		if (l > r) swap(l, r);
		x = ask(l, r);
		printf("%d\n", x);
	}
	return 0;
}
