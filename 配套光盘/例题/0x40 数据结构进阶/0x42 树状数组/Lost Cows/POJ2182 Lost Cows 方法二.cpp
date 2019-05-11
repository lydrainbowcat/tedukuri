//Author:XuHt
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 8006;
int n, t, a[N], c[N], h[N], p[20];

void add(int x) {
	while (x <= n) {
		--c[x];
		x += x & -x;
	}
}

int main() {
	p[0] = 1;
	for (int i = 1; i < 20; i++) p[i] = p[i-1] << 1;
	cin >> n;
	t = log(n) / log(2);
	for (int i = 1; i <= n; i++) {
		++c[i];
		if (i + (i & -i) <= n) c[i+(i&-i)] += c[i];
	}
	a[1] = 1;
	for (int i = 2; i <= n; i++) {
		scanf("%d", &a[i]);
		++a[i];
	}
	for (int i = n; i; i--) {
		int ans = 0, sum = 0;
		for (int j = t; j >= 0; j--)
			if (ans + p[j] <= n && sum + c[ans+p[j]] < a[i]) {
				sum += c[ans+p[j]];
				ans += p[j];
			}
		add(h[i] = ans + 1);
	}
	for (int i = 1; i <= n; i++) printf("%d\n", h[i]);
	return 0;
}
