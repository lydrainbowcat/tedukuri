//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006, INF = 0x3f3f3f3f;
int n, l, r, f[N];
struct T {
	int l, r, x;
	bool operator < (const T w) const {
		return r < w.r;
	}
} a[N], t[N<<2];

void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	if (l == r) {
		t[p].x = f[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	t[p].x = min(t[p<<1].x, t[p<<1|1].x);
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
	if (l <= t[p].l && r >= t[p].r) return t[p].x;
	int mid = (t[p].l + t[p].r) / 2, ans = INF;
	if (l <= mid) ans = min(ans, ask(p << 1, l, r));
	if (r > mid) ans = min(ans, ask(p << 1 | 1, l, r));
	return ans;
}

int main() {
	cin >> n >> l >> r;
	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].x);
	sort(a + 1, a + n + 1);
	memset(f, 0x3f, sizeof(f));
	f[l] = 0;
	build(1, l, r);
	for (int i = 1; i <= n; i++) {
		f[a[i].r] = min(f[a[i].r], ask(1, a[i].l - 1, a[i].r) + a[i].x);
		change(1, a[i].r, f[a[i].r]);
		if (a[i].r >= r) {
			if (f[a[i].r] == INF) puts("-1");
			else cout << f[a[i].r] << endl;
			return 0;
		}
	}
	return 0;
}
