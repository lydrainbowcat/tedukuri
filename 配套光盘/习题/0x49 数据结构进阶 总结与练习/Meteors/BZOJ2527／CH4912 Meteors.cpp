//Author:XuHt
#include <cstdio>
#include <vector>
#include <iostream>
#define ll long long
using namespace std;
const int N = 300006, INF = 0x3f3f3f3f;
struct P {
	int l, r;
	ll a;
} a[N];
ll c[N];
int n, m, k, ans[N];
vector<int> e[N];
pair<int, ll> p[N], p1[N], p2[N];

void add(int x, ll y) {
	while (x <= m) {
		c[x] += y;
		x += x & -x;
	}
}

ll ask(int x) {
	ll ans = 0;
	while (x) {
		ans += c[x];
		x -= x & -x;
	}
	return ans;
}

void get(int i, int w) {
	ll num = w * a[i].a;
	if (a[i].l > a[i].r) add(1, num);
	add(a[i].l, num);
	add(a[i].r + 1, -num);
}

void work(int l, int r, int st, int ed) {
	if (st > ed) return;
	if (l == r) {
		for (int i = st; i <= ed; i++) ans[p[i].first] = l;
		return;
	}
	int mid = (l + r) >> 1, t1 = 0, t2 = 0;
	for (int i = l; i <= mid; i++) get(i, 1);
	for (int i = st; i <= ed; i++) {
		ll tot = 0;
		for (unsigned int j = 0; j < e[p[i].first].size(); j++) {
			tot += ask(e[p[i].first][j]);
			if (tot > p[i].second) break;
		}
		if (tot >= p[i].second) p1[++t1] = p[i];
		else {
			p[i].second -= tot;
			p2[++t2] = p[i];
		}
	}
	for (int i = l; i <= mid; i++) get(i, -1);
	for (int i = 1; i <= t1; i++) p[i+st-1] = p1[i];
	for (int i = 1; i <= t2; i++) p[i+st+t1-1] = p2[i];
	work(l, mid, st, st + t1 - 1);
	work(mid + 1, r, st + t1, ed);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int o;
		scanf("%d", &o);
		e[o].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		p[i].first = i;
		scanf("%lld", &p[i].second);
	}
	cin >> k;
	for (int i = 1; i <= k; i++) {
		scanf("%d %d %lld", &a[i].l, &a[i].r, &a[i].a);
	}
	a[++k].l = 1;
	a[k].r = m;
	a[k].a = INF;
	work(1, k, 1, n);
	for (int i = 1; i <= n; i++)
		ans[i] == k ? puts("NIE") : printf("%d\n", ans[i]);
	return 0;
}
