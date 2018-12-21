//Author:XuHt
#include <cmath>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 500006;
int n, m;
ll a[N], b[N], c[N];
struct T {
	int l, r;
	ll ans;
} t[N*4];

ll gcd(ll x, ll y) {
	return y ? gcd(y, x % y) : x;
}

void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	if (l == r) {
		t[p].ans = b[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	t[p].ans = gcd(t[p<<1].ans, t[p<<1|1].ans);
}

void change_add(int p, int x, ll v) {
	if (t[p].l == t[p].r) {
		t[p].ans += v;
		return;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) change_add(p << 1, x, v);
	else change_add(p << 1 | 1, x, v);
	t[p].ans = gcd(t[p<<1].ans, t[p<<1|1].ans);
}

ll ask_t(int p, int l, int r) {
	if (l <= t[p].l && r >= t[p].r) return t[p].ans;
	int mid = (t[p].l + t[p].r) >> 1;
	ll ans = 0;
	if (l <= mid) ans = gcd(ans, ask_t(p << 1, l, r));
	if (r > mid) ans = gcd(ans, ask_t(p << 1 | 1, l, r));
	return abs(ans);
}

void add(int x, ll y) {
	while (x <= n) {
		c[x] += y;
		x += x & -x;
	}
}

ll ask_c(int x) {
	ll ans = 0;
	while (x) {
		ans += c[x];
		x -= x & -x;
	}
	return ans;
}

int main() {
	cin >> n >> m;
	b[0] = 0;
	memset(c, 0, sizeof(c));
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = a[i] - a[i-1];
	}
	build(1, 1, n);
	while (m--) {
		char ch;
		cin >> ch;
		int l, r;
		cin >> l >> r;
		if (ch == 'C') {
			ll d;
			cin >> d;
			change_add(1, l, d);
			add(l, d);
			if (r + 1 <= n) {
				change_add(1, r + 1, -d);
				add(r + 1, -d);
			}
		} else cout << gcd(a[l] + ask_c(l), ask_t(1, l + 1, r)) << endl;
	}
	return 0;
}
