#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[1000001], b[1000001], n;
double ansxor, ansand, ansor;

void solve(int k)
{
	int last[2] = {0, 0}, c1 = 0, c2 = 0;
	for (int i = 1; i <= n; i++) {
		b[i] = ((a[i] >> k) & 1);
		if (b[i]) {
			ansxor += (1 << k) * 1.0 / n / n;
			ansand += (1 << k) * 1.0 / n / n;
			ansor += (1 << k) * 1.0 / n / n;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (b[i] == 0) {
			ansor += (1 << k) * 2.0 / n / n * last[1];
		} else {
			ansand += (1 << k) * 2.0 / n / n * (i - 1 - last[0]);
			ansor += (1 << k) * 2.0 / n / n * (i - 1);
		}
		ansxor += (1 << k) * 2.0 / n / n * (b[i] ? c1 : c2);
		c1++;
		if (b[i]) swap(c1, c2);
		last[b[i]] = i;
	}
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < 31; i++) solve(i);
	printf("%.3f %.3f %.3f\n", ansxor, ansand, ansor);
}