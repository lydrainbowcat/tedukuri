//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006, INF = 0x3f3f3f3f;
int n, m, f[N], b[N], tot = 0;
struct T {
	int l, r, x;
	bool operator < (const T w) const {
		return r < w.r;
	}
} a[N], t[N<<2];

void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	t[p].x = l ? INF : 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}

void change(int p, int x, int y) {
	if (t[p].l == t[p].r) {
		t[p].x = y;
		return;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) change(p << 1, x, y);
	else change(p << 1 | 1, x, y);
	t[p].x = min(t[p<<1].x, t[p<<1|1].x);
}

int ask(int p, int l, int r) {
	if (t[p].l >= l && t[p].r <= r) return t[p].x;
	int mid = (t[p].l + t[p].r) >> 1, ans = INF;
	if (l <= mid) ans = min(ans, ask(p << 1, l, r));
	if (r > mid) ans = min(ans, ask(p << 1 | 1, l, r));
	return ans;
}

int main() {
	cin >> n >> m;
	b[++tot] = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].l, &a[i].r);
		b[++tot] = a[i].l;
		b[++tot] = a[i].l + 1;
		b[++tot] = a[i].r;
		b[++tot] = a[i].r + 1;
	}
	b[++tot] = m;
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - (b + 1);
	while (b[tot] > m) --tot;
	sort(a + 1, a + n + 1);
	build(1, 0, tot);
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; i++) {
		a[i].r = lower_bound(b + 1, b + tot + 1, a[i].r) - b;
		a[i].l = lower_bound(b + 1, b + tot + 1, a[i].l) - b;
		int num = ask(1, a[i].l - 1, a[i].r - 1) + 1;
		if (f[a[i].r] > num) {
			f[a[i].r] = num;
			change(1, a[i].r, f[a[i].r]);
		}
	}
	if (f[tot] == INF) puts("-1");
	else cout << f[tot] << endl;
	return 0;
}
