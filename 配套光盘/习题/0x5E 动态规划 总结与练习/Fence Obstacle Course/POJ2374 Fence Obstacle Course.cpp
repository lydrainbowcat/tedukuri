//Author:XuHt
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50006, S = 200006, X = 100000;
int n, s, l[N], r[N], f[N][2];
struct T {
	int l, r, x;
} t[S<<2];

void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	t[p].x = (l == r ? 0 : -1);
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}

void change(int p, int l, int r, int x) {
	if (t[p].l >= l && t[p].r <= r) {
		t[p].x = x;
		return;
	}
	if (t[p].l != t[p].r && t[p].x != -1) {
		t[p<<1].x = t[p<<1|1].x = t[p].x;
		t[p].x = -1;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) change(p << 1, l, r, x);
	if (r > mid) change(p << 1 | 1, l, r, x);
}

int ask(int p, int x) {
	if (t[p].l == t[p].r) return t[p].x;
	if (t[p].l != t[p].r && t[p].x != -1) {
		t[p<<1].x = t[p<<1|1].x = t[p].x;
		t[p].x = -1;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	return ask(x <= mid ? (p << 1) : (p << 1 | 1), x);
}

int main() {
	cin >> n >> s;
	build(1, 0, X << 1);
	l[0] = r[0] = X;
	s += X;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &l[i], &r[i]);
		l[i] += X;
		r[i] += X;
		int w = ask(1, l[i]);
		f[i][0] = min(f[w][0] + abs(l[i] - l[w]), f[w][1] + abs(l[i] - r[w]));
		w = ask(1, r[i]);
		f[i][1] = min(f[w][0] + abs(r[i] - l[w]), f[w][1] + abs(r[i] - r[w]));
		change(1, l[i], r[i], i);
	}
	cout << min(f[n][0] + s - l[n], f[n][1] - s + r[n]) << endl;
	return 0;
}
