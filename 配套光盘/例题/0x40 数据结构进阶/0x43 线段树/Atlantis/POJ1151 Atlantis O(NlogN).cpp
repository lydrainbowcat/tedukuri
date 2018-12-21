//Author:XuHt
#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106;
int n, m, num = 0;
struct P {
	double x, y, z;
	int k;
	bool operator < (const P w) const {
		return x < w.x;
	}
} a[N<<1];
double raw[N<<1];
map<double, int> val;
struct T {
	int l, r, cnt;
	double len;
} t[N<<3];

void build(int p, int l, int r) {
	t[p].l = l;
	t[p].r = r;
	t[p].cnt = 0;
	t[p].len = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}

void change(int p, int l, int r, double k) {
	if (l <= t[p].l && r >= t[p].r) t[p].len = ((t[p].cnt += k) ? raw[t[p].r+1] - raw[t[p].l] : 0);
	if (t[p].l == t[p].r) return;
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) change(p << 1, l, r, k);
	if (r > mid) change(p << 1 | 1, l, r, k);
	t[p].len = (t[p].cnt ? raw[t[p].r+1] - raw[t[p].l] : t[p<<1].len + t[p<<1|1].len);
}

void Atlantis() {
	for (int i = 1; i <= n; i++) {
		int k = i << 1;
		double y, z;
		scanf("%lf %lf %lf %lf", &a[k-1].x, &y, &a[k].x, &z);
		raw[k-1] = a[k-1].y = a[k].y = y;
		raw[k] = a[k-1].z = a[k].z = z;
		a[k-1].k = 1;
		a[k].k = -1;
	}
	n <<= 1;
	sort(raw + 1, raw + n + 1);
	int m = unique(raw + 1, raw + n + 1) - (raw + 1);
	for (int i = 1; i <= m; i++) val[raw[i]] = i;
	sort(a + 1, a + n + 1);
	build(1, 1, m - 1);
	double ans = 0;
	for (int i = 1; i < n; i++) {
		int y = val[a[i].y], z = val[a[i].z] - 1;
		change(1, y, z, a[i].k);
		ans += t[1].len * (a[i+1].x - a[i].x);
	}
	printf("Test case #%d\nTotal explored area: %.2f\n\n", ++num, ans);
}

int main() {
	while (cin >> n && n) Atlantis();
	return 0;
}
