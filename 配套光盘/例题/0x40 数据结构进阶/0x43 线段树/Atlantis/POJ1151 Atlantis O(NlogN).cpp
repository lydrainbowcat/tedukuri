//Author:xht37
#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ls (p << 1)
#define rs (ls | 1)
#define mid ((t[p].l + t[p].r) >> 1)
using namespace std;
const int N = 1e5 + 6;
int n, m, num;
struct P {
	double x, y, z;
	int k;
	inline bool operator < (const P &o) const {
		return x < o.x;
	}
} a[N<<1];
double raw[N<<1];
map<double, int> val;
struct T {
	int l, r, cnt;
	double len;
} t[N<<3];

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r, t[p].cnt = 0, t[p].len = 0;
	if (l == r) return;
	build(ls, l, mid), build(rs, mid + 1, r);
}

void change(int p, int l, int r, double k) {
	if (l <= t[p].l && r >= t[p].r) return t[p].len = ((t[p].cnt += k) ? raw[t[p].r+1] - raw[t[p].l] : (t[p].l == t[p].r ? 0 : t[ls].len + t[rs].len)), void();
	if (l <= mid) change(ls, l, r, k);
	if (r > mid) change(rs, l, r, k);
	t[p].len = (t[p].cnt ? raw[t[p].r+1] - raw[t[p].l] : t[ls].len + t[rs].len);
}

inline void Atlantis() {
	for (int i = 1; i <= n; i++) {
		int k = i << 1;
		double y, z;
		scanf("%lf %lf %lf %lf", &a[k-1].x, &y, &a[k].x, &z);
		raw[k-1] = a[k-1].y = a[k].y = y;
		raw[k] = a[k-1].z = a[k].z = z;
		a[k-1].k = 1, a[k].k = -1;
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
