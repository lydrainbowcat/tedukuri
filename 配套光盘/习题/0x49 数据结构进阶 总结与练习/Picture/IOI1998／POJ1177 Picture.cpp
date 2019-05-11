//Author:XuHt
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 20006, INF = 0x3f3f3f3f;
int n, Max = -INF, Min = INF, tot, ans, pre;
struct P {
	int l, r, h, k;
	bool operator < (const P p) const {
		return h < p.h || (h == p.h && k > p.k);
	}
} a[N];
struct T {
	int sum, num, len;
	bool l, r;
} t[N<<2];

void add(int l, int r, int h, int k) {
	a[++tot].l = l;
	a[tot].r = r;
	a[tot].h = h;
	a[tot].k = k;
}

void work(int p, int l, int r) {
	if (t[p].sum) {
		t[p].num = t[p].l = t[p].r = 1;
		t[p].len = r - l + 1;
	} else if (l == r) t[p].len = t[p].num = t[p].l = t[p].r = 0;
	else {
		t[p].len = t[p<<1].len + t[p<<1|1].len;
		t[p].num = t[p<<1].num + t[p<<1|1].num;
		if (t[p<<1].r && t[p<<1|1].l) --t[p].num;
		t[p].l = t[p<<1].l;
		t[p].r = t[p<<1|1].r;
	}
}

void change(int p, int l, int r, int L, int R, int k) {
	if (l >= L && r <= R) {
		t[p].sum += k;
		work(p, l, r);
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid) change(p << 1, l, mid, L, R, k);
	if (R > mid) change(p << 1 | 1, mid + 1, r, L, R, k);
	work(p, l, r);
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		Max = max(Max, max(x1, x2));
		Min = min(Min, min(x1, x2));
		add(x1, x2, y1, 1);
		add(x1, x2, y2, -1);
	}
	if (Min <= 0) {
		for (int i = 1; i <= tot; i++) {
			a[i].l += 1 - Min;
			a[i].r += 1 - Min;
		}
		Max -= Min;
	}
	sort(a + 1, a + tot + 1);
	for (int i = 1; i <= tot; i++) {
		change(1, 1, Max, a[i].l, a[i].r - 1, a[i].k);
		while (a[i].h == a[i+1].h && a[i].k == a[i+1].k) {
			i++;
			change(1, 1, Max, a[i].l, a[i].r - 1, a[i].k);
		}
		ans += abs(t[1].len - pre);
		pre = t[1].len;
		ans += t[1].num * (a[i+1].h - a[i].h) << 1;
	}
	cout << ans << endl;
	return 0;
}
