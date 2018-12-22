//Author:XuHt
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006, INF = 0x3f3f3f3f;
int n, m, a[N], b[N<<1], tot, root[N<<3];
struct Treap {
	int l, r, val, dat, s;
} T[N*20];
struct Tree {
	int l, r;
} t[N<<3];
struct Q {
	char s[2];
	int x, y, z;
} q[N];

int New(int val) {
	T[++tot].val = val;
	T[tot].dat = rand();
	T[tot].s = 1;
	return tot;
}

void Update(int p) {
	T[p].s = T[T[p].l].s + T[T[p].r].s + 1;
}

void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	T[root[p]=New(-INF)].r = New(INF);
	Update(root[p]);
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}

int Get(int p, int val) {
	if (!p) return 0;
	if (val == T[p].val) return T[T[p].l].s + 1;
	if (val < T[p].val) return Get(T[p].l, val);
	return Get(T[p].r, val) + T[T[p].l].s + 1;
}

void Zig(int &p) {
	int q = T[p].l;
	T[p].l = T[q].r;
	T[q].r = p;
	p = q;
	Update(T[p].r);
	Update(p);
}

void Zag(int &p) {
	int q = T[p].r;
	T[p].r = T[q].l;
	T[q].l = p;
	p = q;
	Update(T[p].l);
	Update(p);
}

void Add(int &p, int val) {
	if (!p) {
		p = New(val);
		return;
	}
	if (val < T[p].val) {
		Add(T[p].l, val);
		if (T[p].dat < T[T[p].l].dat) Zig(p);
	} else {
		Add(T[p].r, val);
		if (T[p].dat < T[T[p].r].dat) Zag(p);
	}
	Update(p);
}

void add(int p, int x, int val) {
	Add(root[p], val);
	if (t[p].l == t[p].r) return;
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) add(p << 1, x, val);
	else add(p << 1 | 1, x, val);
}

void Re(int &p, int val) {
	if (!p) return;
	if (val == T[p].val) {
		if (T[p].l || T[p].r) {
			if (T[T[p].l].dat > T[T[p].r].dat) {
				Zig(p);
				Re(T[p].r, val);
			} else {
				Zag(p);
				Re(T[p].l, val);
			}
			Update(p);
		} else p = 0;
		return;
	}
	Re(val < T[p].val ? T[p].l : T[p].r, val);
	Update(p);
}

void re(int p, int x, int val) {
	Re(root[p], val);
	if (t[p].l == t[p].r) return;
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) re(p << 1, x, val);
	else re(p << 1 | 1, x, val);
}

int Find(int p) {
	int now = T[p].val;
	if (now != -INF && now != INF) return now;
	if (T[p].l) {
		now = Find(T[p].l);
		if (now) return now;
	}
	if (T[p].r) {
		now = Find(T[p].r);
		if (now) return now;
	}
	return 0;
}

int ask(int p, int l, int r, int k) {
	if (t[p].l == t[p].r) return Find(root[p]);
	int cnt = Get(root[p<<1], r) - Get(root[p<<1], l - 1);
	if (k <= cnt) return ask(p << 1, l, r, k);
	else return ask(p << 1 | 1, l, r, k - cnt);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	int tb = n;
	for (int i = 1; i <= m; i++) {
		scanf("%s %d %d", q[i].s, &q[i].x, &q[i].y);
		if (q[i].s[0] == 'Q') scanf("%d", &q[i].z);
		else b[++tb] = q[i].y;
	}
	sort(b + 1, b + tb + 1);
	int w = unique(b + 1, b + tb + 1) - (b + 1);
	build(1, 1, w);
	for (int i = 1; i <= n; i++) {
		a[i] = lower_bound(b + 1, b + w + 1, a[i]) - b;
		add(1, a[i], i);
	}
	for (int i = 1; i <= m; i++)
		if (q[i].s[0] == 'Q') {
			int ans = ask(1, q[i].x, q[i].y, q[i].z);
			printf("%d\n", b[a[ans]]);
		} else {
			q[i].y = lower_bound(b + 1, b + w + 1, q[i].y) - b;
			re(1, a[q[i].x], q[i].x);
			add(1, q[i].y, q[i].x);
			a[q[i].x] = q[i].y;
		}
	return 0;
}
