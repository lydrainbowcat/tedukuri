//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006;
int n, m, tot = 0, root[N];
struct T {
	int l, r, f, d;
} t[N<<5];

inline int build(int l, int r) {
	int p = ++tot;
	if (l == r) {
		t[p].f = l;
		t[p].d = 1;
		return p;
	}
	int mid = (l + r) >> 1;
	t[p].l = build(l, mid);
	t[p].r = build(mid + 1, r);
	return p;
}

inline int ask(int p, int l, int r, int x) {
	while (l < r) {
		int mid = (l + r) >> 1;
		if (x <= mid) {
			r = mid;
			p = t[p].l;
		} else {
			l = mid + 1;
			p = t[p].r;
		}
	}
	return p;
}

inline int add(int pre, int l, int r, int x) {
	int p = ++tot;
	if (l == r) {
		t[p].f = x;
		t[p].d = t[pre].d + 1;
		return p;
	}
	t[p].l = t[pre].l;
	t[p].r = t[pre].r;
	int mid = (l + r) >> 1;
	if (x <= mid) t[p].l = add(t[pre].l, l, mid, x);
	else t[p].r = add(t[pre].r, mid + 1, r, x);
	return p;
}

inline int add(int pre, int l, int r, int s, int f) {
	int p = ++tot;
	if (l == r) {
		t[p].f = f;
		t[p].d = t[pre].d;
		return p;
	}
	t[p].l = t[pre].l;
	t[p].r = t[pre].r;
	int mid = (l + r) >> 1;
	if (s <= mid) t[p].l = add(t[pre].l, l, mid, s, f);
	else t[p].r = add(t[pre].r, mid + 1, r, s, f);
	return p;
}

inline int get(int p, int x) {
	int k = ask(p, 1, n, x);
	if (t[k].f == x) return k;
	return get(p, t[k].f);
}

int main() {
	cin >> n >> m;
	root[0] = build(1, n);
	int ans = 0, o, x, y;
	for (int i = 1; i <= m; i++) {
		root[i] = root[i-1];
		scanf("%d", &o);
		if (o == 1) {
			scanf("%d %d", &x, &y);
			int rx = get(root[i], x ^= ans);
			int ry = get(root[i], y ^= ans);
			if (t[rx].f == t[ry].f) continue;
			if (t[rx].d > t[ry].d) swap(rx, ry);
			root[i] = add(root[i-1], 1, n, t[rx].f, t[ry].f);
			if (t[rx].d == t[ry].d)
				root[i] = add(root[i], 1, n, t[ry].f);
		} else if (o == 2) {
			scanf("%d", &x);
			root[i] = root[x^=ans];
		} else {
			scanf("%d %d", &x, &y);
			int rx = get(root[i], x ^= ans);
			int ry = get(root[i], y ^= ans);
			printf("%d\n", ans = rx == ry);
		}
	}
	return 0;
}
