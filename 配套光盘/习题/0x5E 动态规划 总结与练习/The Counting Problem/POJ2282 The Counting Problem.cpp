//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

void dfs(int n, int *f, int x) {
	if (n <= 0) return;
	int w = n % 10 + 1, z = n / 10;
	for (int i = 1; i < w; i++) f[i] += x;
	while (z) {
		f[z%10] += w * x;
		z /= 10;
	}
	for (int i = 0; i <= 9; i++) f[i] += n / 10 * x;
	dfs(n / 10 - 1, f, x * 10);
}

int main() {
	int x, y;
	while (cin >> x >> y && (x || y)) {
		int a[10], b[10];
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		if (x > y) swap(x, y);
		if (--x < y) {
			dfs(y, b, 1);
			dfs(x, a, 1);
		}
		for (int i = 0; i < 9; i++) printf("%d ", b[i] - a[i]);
		printf("%d\n", b[9] - a[9]);
	}
	return 0;
}
