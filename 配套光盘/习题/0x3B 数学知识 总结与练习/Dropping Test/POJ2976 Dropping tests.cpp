//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006;
const double eps = 1e-8;
int n, k, a[N], b[N];
double c[N];

void Dropping_tests() {
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	double l = 0, r = 1;
	for (int i = 1; i < 101; i++) {
		double mid = (l + r) / 2;
		for (int j = 1; j <= n; j++)
			c[j] = a[j] - b[j] * mid;
		sort(c + 1, c + n + 1);
		double ans = 0;
		for (int j = k + 1; j <= n; j++)
			ans += c[j];
		if (ans > eps) l = mid;
		else r = mid;
	}
	printf("%.0f\n", (l + r) * 50);
}

int main() {
	while (cin >> n >> k && n) Dropping_tests();
	return 0;
}
