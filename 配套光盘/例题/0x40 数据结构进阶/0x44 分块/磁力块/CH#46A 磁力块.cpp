//Author:XuHt
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 250006;
struct P {
	int x, y, m, p, r;
} p[N], q[N];
bool b[N];
int n, L[N], R[N], M[N];

bool cmp(P a, P b) {
	return a.m < b.m;
}

bool cmp0(P a, P b) {
	return (ll)(a.x - q[0].x) * (a.x - q[0].x) + (ll)(a.y - q[0].y) * (a.y - q[0].y) < (ll)(b.x - q[0].x) * (b.x - q[0].x) + (ll)(b.y - q[0].y) * (b.y - q[0].y);
}

bool pd(P a, P b) {
	return (ll)(q[0].x - b.x) * (q[0].x - b.x) + (ll)(q[0].y - b.y) * (q[0].y - b.y) <= (ll)a.r * a.r;
}

int main() {
	cin >> q[0].x >> q[0].y >> q[0].p >> q[0].r >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d %d %d %d %d", &p[i].x, &p[i].y, &p[i].m, &p[i].p, &p[i].r);
	sort(p + 1, p + n + 1, cmp);
	int t = sqrt(n);
	for (int i = 1; i <= t; i++) {
		L[i] = (i - 1) * t + 1;;
		R[i] = i * t;
		M[i] = p[R[i]].m;
		sort(p + L[i], p + R[i] + 1, cmp0);
	}
	if (R[t] < n) {
		L[t+1] = R[t] + 1;
		R[++t] = n;
		M[t] = p[R[t]].m;
		sort(p + L[t], p + R[t] + 1, cmp0);
	}
	int l = 0, r = 1;
	memset(b, 0, sizeof(b));
	while (l < r) {
		int k = 0;
		for (int i = 1; i <= t; i++)
			if (M[i] <= q[l].p) k = i;
			else break;
		for (int i = 1; i <= k; i++)
			while (L[i] <= R[i] && pd(q[l], p[L[i]])) {
				if (!b[L[i]]) {
					b[L[i]] = 1;
					q[r++] = p[L[i]];
				}
				++L[i];
			}
		if (t != k++)
			for (int i = L[k]; i <= R[k]; i++)
				if (!b[i] && p[i].m <= q[l].p && pd(q[l], p[i])) {
					b[i] = 1;
					q[r++] = p[i];
				}
		++l;
	}
	cout << r - 1 << endl;
	return 0;
}
