//Author:XuHt
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006, INF = 0x3f3f3f3f;
const double eps = 1e-6;
int n;
struct P {
	int x, y, z;
} p[N];
double a[N][N], b[N][N], c[N][N], d[N];
bool v[N];

inline double s(int i, int j) {
	return sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
}

double work(double k) {
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			if (i == j) c[i][j] = INF;
			else c[i][j] = c[j][i] = a[i][j] - k * b[i][j];
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= n; i++) d[i] = INF;
	d[1] = 0;
	double ans = 0;
	while (1) {
		int x = 0;
		for (int i = 1; i <= n; i++)
			if (!v[i] && (!x || d[x] > d[i])) x = i;
		if (!x) break;
		v[x] = 1;
		ans += d[x];
		for (int i = 1; i <= n; i++) d[i] = min(d[i], c[x][i]);
	}
	return ans;
}

void Desert_King() {
	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].z);
	double num = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			num += (a[i][j] = a[j][i] = abs(p[i].z - p[j].z));
			b[i][j] = b[j][i] = s(i, j);
		}
	double l = 0, r = num;
	while (l + eps <= r) {
		double mid = (l + r) / 2;
		if (work(mid) >= 0) l = mid;
		else r = mid;
	}
	printf("%.3f\n", l);
}

int main() {
	while (cin >> n && n) Desert_King();
	return 0;
}
