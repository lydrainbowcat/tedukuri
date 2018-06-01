#include<iostream>
#include<cstdio>
#include<algorithm> 
using namespace std;
const int SIZE = 500010;
struct SegmentTree {
	int l, r;
	long long dat;
} t[SIZE * 4];
long long a[SIZE], b[SIZE], c[SIZE];
int n, m;

long long gcd(long long a, long long b) {
	return b ? gcd(b, a%b) : a;
}

// 维护区间gcd的线段树 
void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l==r) { t[p].dat = b[l]; return; }
	int mid = (l + r) / 2;
	build(p*2, l, mid);
	build(p*2+1, mid+1, r);
	t[p].dat = gcd(t[p*2].dat, t[p*2+1].dat);
}

void change(int p, int x, long long v) {
	if (t[p].l == t[p].r) { t[p].dat += v; return; }
	int mid = (t[p].l + t[p].r) / 2;
	if (x <= mid) change(p*2, x, v);
	else change(p*2+1, x, v);
	t[p].dat = gcd(t[p*2].dat, t[p*2+1].dat);
}

long long ask(int p, int l, int r) {
	if (l <= t[p].l && r >= t[p].r) return abs(t[p].dat);
	int mid = (t[p].l + t[p].r) / 2;
	long long val = 0;
	if (l<=mid) val = gcd(val, ask(p*2, l, r));
	if (r>mid) val = gcd(val, ask(p*2+1, l, r));
	return abs(val);
}

long long sum(int x) {
	long long y = 0;
	for (; x; x -= x & -x) y += c[x];
	return y;
}

void add(int x, long long y) {
	for (; x <= n; x += x & -x) c[x] += y;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		b[i] = a[i] - a[i-1];
	}
	build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		char str[2]; scanf("%s", str);
		int l, r; scanf("%d%d", &l, &r);
		if (str[0] == 'Q') {
			long long al = a[l] + sum(l);
			long long val = l < r ? ask(1, l + 1, r) : 0;
			printf("%lld\n", gcd(al, val));
		} else {
			long long delta; scanf("%lld", &delta);
			change(1, l, delta);
			if (r < n) change(1, r + 1, -delta);
			add(l, delta);
			add(r + 1, -delta);
		}
	}
}
