//Author:XuHt
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ld long double
using namespace std;
const int N = 100006;
const double INF = 0x3f3f3f3f, eps = 0.000001;
struct P {
	int x, y;
	bool z;
	bool operator < (const P w) const {
		return x < w.x;
	}
} p[N*2];
int n;

double s(P x, P y) {
	if (x.z == y.z) return INF;
	return sqrt((ld)(x.x - y.x) * (x.x - y.x) + (ld)(x.y - y.y) * (x.y - y.y));
}

double s(int l, int r) {
	if (l == r) return INF;
	if (l + 1 == r) return s(p[l], p[r]);
	int mid = (l + r) >> 1;
	double ans = min(s(l, mid), s(mid, r));
	for (int i = mid - 1; i >= l; i--) {
		if (p[mid].x - p[i].x + eps > ans) break;
		for (int j = mid + 1; j <= r; j++) {
			if (p[j].x - p[i].x + eps > ans) break;
			ans = min(ans, s(p[i], p[j]));
		}
	}
	return ans;
}

void Raid() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &p[i].x, &p[i].y);
		p[i].z = 0;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &p[i+n].x, &p[i+n].y);
		p[i+n].z = 1;
	}
	sort(p + 1, p + 2 * n + 1);
	printf("%.3f\n", s(1, 2 * n));
}

int main() {
	int t;
	cin >> t;
	while (t--) Raid();
	return 0;
}
