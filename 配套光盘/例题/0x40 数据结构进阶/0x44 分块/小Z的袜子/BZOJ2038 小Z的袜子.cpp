//Author:XuHt
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 50006;
int n, m, c[N], L[N], R[N], num[N];
struct P {
	int id, l, r;
} p[N];
ll ans, Ans[N][2], g;

bool cmp(P a, P b) {
	return a.l < b.l || (a.l == b.l && a.r < b.r);
}

bool cmp0(P a, P b) {
	return a.r < b.r;
}

void work(int x, int w) {
	ans -= (ll)num[x] * (num[x] - 1);
	num[x] += w;
	ans += (ll)num[x] * (num[x] - 1);
}

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &p[i].l, &p[i].r);
		p[i].id = i;
	}
	sort(p + 1, p + m + 1, cmp);
	int t = sqrt(m);
	for (int i = 1; i <= t; i++) {
		L[i] = (i - 1) * t + 1;
		R[i] = i * t;
	}
	if (R[t] < m) {
		L[t+1] = R[t] + 1;
		R[++t] = m;
	}
	for (int i = 1; i <= t; i++) {
		sort(p + L[i], p + R[i] + 1, cmp0);
		memset(num, 0, sizeof(num));
		ans = 0;
		int l = p[L[i]].l, r = p[L[i]].r;
		for (int j = l; j <= r; j++) work(c[j], 1);
		Ans[p[L[i]].id][0] = ans;
		Ans[p[L[i]].id][1] = (ll)(r - l) * (r - l + 1);
		g = gcd(Ans[p[L[i]].id][0], Ans[p[L[i]].id][1]);
		if (!g) Ans[p[L[i]].id][1] = 1;
		else {
			Ans[p[L[i]].id][0] /= g;
			Ans[p[L[i]].id][1] /= g;
		}
		for (int j = L[i] + 1; j <= R[i]; j++) {
			while (r < p[j].r) work(c[++r], 1);
			while (r > p[j].r) work(c[r--], -1);
			while (l < p[j].l) work(c[l++], -1);
			while (l > p[j].l) work(c[--l], 1);
			if (p[j].l == p[j].r) {
				Ans[p[j].id][0] = 0;
				Ans[p[j].id][1] = 1;
			} else {
				Ans[p[j].id][0] = ans;
				Ans[p[j].id][1] = (ll)(r - l) * (r - l + 1);
				g = gcd(Ans[p[j].id][0], Ans[p[j].id][1]);
				if (!g) Ans[p[j].id][1] = 1;
				else {
					Ans[p[j].id][0] /= g;
					Ans[p[j].id][1] /= g;
				}
			}
		}
	}
	for (int i = 1; i <= m; i++)
		printf("%lld/%lld\n", Ans[i][0], Ans[i][1]);
	return 0;
}
