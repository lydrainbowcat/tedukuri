//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006;
struct T {
	int l, r, ls, rs, s, p;
} t[N];
int n, m;

void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	t[p].s = t[p].ls = t[p].rs = r - l + 1;
	t[p].p = -1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}

void spread(int p) {
	t[p<<1].p = t[p<<1|1].p = t[p].p;
	if (t[p<<1].p) {
		t[p<<1].ls = t[p<<1].rs = t[p<<1].s = t[p<<1].r - t[p<<1].l + 1;
		t[p<<1|1].ls = t[p<<1|1].rs = t[p<<1|1].s = t[p<<1|1].r - t[p<<1|1].l + 1;
	} else t[p<<1].ls = t[p<<1].rs = t[p<<1].s = t[p<<1|1].ls = t[p<<1|1].rs = t[p<<1|1].s = 0;
	t[p].p = -1;
}

void change(int p) {
	t[p].ls = t[p<<1].ls;
	t[p].rs = t[p<<1|1].rs;
	if (t[p<<1].ls == t[p<<1].r - t[p<<1].l + 1) t[p].ls += t[p<<1|1].ls;
	if (t[p<<1|1].rs == t[p<<1|1].r - t[p<<1|1].l + 1) t[p].rs += t[p<<1].rs;
	t[p].s = max(max(t[p<<1].s, t[p<<1|1].s), t[p<<1].rs + t[p<<1|1].ls);
}

int ask(int p, int d) {
	if (t[p].l == t[p].r) return t[p].l;
	if (t[p].p != -1) spread(p);
	if (t[p<<1].s >= d) return ask(p << 1, d);
	int mid = (t[p].l + t[p].r) >> 1;
	if (t[p<<1].rs + t[p<<1|1].ls >= d) return mid - t[p<<1].rs + 1;
	if (t[p<<1|1].s >= d) return ask(p << 1 | 1, d);
	return -1;
}

void change1(int p, int l, int r) {
	if (t[p].l >= l && t[p].r <= r) {
		t[p].ls = t[p].rs = t[p].s = t[p].p = 0;
		return;
	}
	if (t[p].p != -1) spread(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) change1(p << 1, l, r);
	if (r > mid) change1(p << 1 | 1, l, r);
	change(p);
}

void change2(int p, int l, int r) {
	if (t[p].l >= l && t[p].r <= r) {
		t[p].ls = t[p].rs = t[p].s = t[p].r - t[p].l + 1;
		t[p].p = 1;
		return;
	}
	if (t[p].p != -1) spread(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) change2(p << 1, l, r);
	if (r > mid) change2(p << 1 | 1, l, r);
	change(p);
}

int main() {
	cin >> n >> m;
	build(1, 1, n);
	while (m--) {
		int op, x, d;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &d);
			if (t[1].s < d) puts("0");
			else {
				int ans = ask(1, d);
				printf("%d\n", ans);
				change1(1, ans, ans + d - 1);
			}
		} else {
			scanf("%d %d", &x, &d);
			change2(1, x, x + d - 1);
		}
	}
	return 0;
}
