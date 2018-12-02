//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 60006;
int ans[1000000], len = 1, p[N*2], c[N*2], tot = 0;
bool v[N*2];

void gj(int x) {
	for (int i = 1; i <= len; i++) ans[i] *= x;
	len += 6;
	for (int i = 1; i <= len; i++) {
		ans[i+1] += ans[i] / 10;
		ans[i] %= 10;
	}
	while (!ans[len]) len--;
}

int main() {
	int n;
	cin >> n;
	ans[0] = 0;
	ans[1] = 1;
	memset(v, 0, sizeof(v));
	for (int i = 2; i <= n * 2; i++)
		if (!v[i]) {
			p[++tot] = i;
			for (int j = i; j <= n * 2; j += i) v[j] = 1;
		}
	memset(c, 0, sizeof(c));
	for (int i = 1; i <= tot; i++) {
		int a = p[i];
		while (a <= n * 2) {
			c[i] += n * 2 / a - n / a - (n + 1) / a;
			a *= p[i];
		}
		while (c[i]--) gj(p[i]);
	}
	for (int i = len; i; i--) printf("%d", ans[i]);
	cout << endl;
	return 0;
}
