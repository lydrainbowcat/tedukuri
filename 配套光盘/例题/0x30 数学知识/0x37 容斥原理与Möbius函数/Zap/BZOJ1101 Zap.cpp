//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50001;
int miu[N];
bool v[N];

void Zap() {
	int a, b, k, ans = 0;
	scanf("%d %d %d", &a, &b, &k);
	a /= k;
	b /= k;
	if (a > b) swap(a, b);
	for (int x = 1, gx; x <= a; x = gx + 1) {
		gx = min(a / (a / x), b / (b / x));
		ans += (miu[gx] - miu[x-1]) * (a / x) * (b / x);
	}
	printf("%d\n", ans);
}

int main() {
	for (int i = 1; i < N; i++) {
		miu[i] = 1;
		v[i] = 0;
	}
	for (int i = 2; i < N; i++) {
		if (v[i]) continue;
		miu[i] = -1;
		for (int j = 2 * i; j < N; j += i) {
			v[j] = 1;
			if (j / i % i == 0) miu[j] = 0;
			else miu[j] *= -1;
		}
	}
	for (int i = 1; i < N; i++) miu[i] += miu[i-1];
	int n;
	cin >> n;
	while (n--) Zap();
	return 0;
}
