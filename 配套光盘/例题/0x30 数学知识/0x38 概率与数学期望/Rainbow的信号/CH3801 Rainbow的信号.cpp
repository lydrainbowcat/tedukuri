//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006;
int n, a[N], b[N];
double ansxor = 0, ansand = 0, ansor = 0;

void Rainbow(int k) {
	int last[2] = {0,0}, c1 = 0, c2 = 0;
	double w = (double)(1 << k) / n / n;
	for (int i = 1; i <= n; i++) {
		b[i] = ((a[i] >> k) & 1);
		if (b[i]) {
			ansxor += w;
			ansand += w;
			ansor += w;
		}
		if (!b[i]) ansor += w * last[1] * 2;
		else {
			ansand += w * (i - 1 - last[0]) * 2;
			ansor += w * (i - 1) * 2;
		}
		ansxor += w * (b[i] ? c1 : c2) * 2;
		c1++;
		if (b[i]) swap(c1, c2);
		last[b[i]] = i;
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < 31; i++) Rainbow(i);
	printf("%.3f %.3f %.3f\n", ansxor, ansand, ansor);
	return 0;
}
