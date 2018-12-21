//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10006;
int n;
struct P {
	unsigned int x, y, z;
	int c;
	bool operator < (const P w) const {
		return x < w.x || (x == w.x && c < w.c);
	}
} a[N<<1];
unsigned int w, h, b[N<<1];
struct T {
	int l, r, ans, add;
} t[N<<3];

void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	t[p].ans = t[p].add = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}

void spread(int p) {
	t[p<<1].add += t[p].add;
	t[p<<1].ans += t[p].add;
	t[p<<1|1].add += t[p].add;
	t[p<<1|1].ans += t[p].add;
	t[p].add = 0;
}

void change(int p, int l, int r, int c) {
	if (l <= t[p].l && r >= t[p].r) {
		t[p].add += c;
		t[p].ans += c;
		return;
	}
	if (t[p].add) spread(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) change(p<<1, l, r, c);
	if (r > mid) change(p<<1|1, l, r, c);
	t[p].ans = max(t[p<<1].ans, t[p<<1|1].ans);
}

void Stars_in_Your_Window() {
	for (int i = 1; i <= n; i++) {
		int k = i << 1;
		scanf("%u %u %d", &a[k-1].x, &a[k-1].y, &a[k-1].c);
		a[k].x = a[k-1].x + w;
		b[k-1] = a[k].y = a[k-1].y;
		b[k] = a[k].z = a[k-1].z = a[k].y + h - 1;
		a[k].c = -a[k-1].c;
	}
	n <<= 1;
	sort(b + 1, b + n + 1);
	int m = unique(b + 1, b + n + 1) - (b + 1);
	for (int i = 1; i <= n; i++) {
		a[i].y = lower_bound(b + 1, b + m + 1, a[i].y) - b;
		a[i].z = lower_bound(b + 1, b + m + 1, a[i].z) - b;
	}
	sort(a + 1, a + n + 1);
	build(1, 1, m);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		change(1, a[i].y, a[i].z, a[i].c);
		ans = max(ans, t[1].ans);
	}
	cout << ans << endl;
}

int main() {
	while (cin >> n >> w >> h) Stars_in_Your_Window();
	return 0;
}
