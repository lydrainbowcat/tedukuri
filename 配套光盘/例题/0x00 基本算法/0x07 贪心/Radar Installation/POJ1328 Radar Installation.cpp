//Author:XuHt
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ld long double
using namespace std;
const int N = 1006;
const double INF = -0x3f3f3f3f, eps = 0.000001;
int n, d, num = 0;
struct P {
	int x, y;
	double l, r;
	bool operator < (const P x) const {
		return l < x.l;
	}
} p[N];

void Radar_Installation() {
	for (int i = 1; i <= n; i++) scanf("%d %d", &p[i].x, &p[i].y);
	bool b = 1;
	for (int i = 1; i <= n; i++)
		if (p[i].y > d) {
			b = 0;
			break;
		}
	if (!b) {
		cout << "Case " << ++num << ": -1" << endl;
		return;
	}
	for (int i = 1; i <= n; i++) {
		ld k = sqrt((ld)d * d - (ld)p[i].y * p[i].y);
		p[i].l = p[i].x - k, p[i].r = p[i].x + k;
	}
	sort(p + 1, p + n + 1);
	int ans = 1;
	double pos = -INF;
	for (int i = 1; i <= n; i++) {
		if (pos + eps < p[i].l) {
			ans++;
			pos = p[i].r;
		} else pos = min(p[i].r, pos);
	}
	cout << "Case " << ++num << ": " << ans << endl;
}

int main() {
	while (cin >> n >> d && n && d) Radar_Installation();
	return 0;
}
