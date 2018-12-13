//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1006;
int	n, sg[N];

int fj(int x, int *a) {
	int tot = a[1] = 1;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0) {
			a[++tot] = i;
			if (i * i != x) a[++tot] = x / i;
		}
	return tot;
}

int SG(int x) {
	if (sg[x] != -1) return sg[x];
	int a[N];
	int tot = fj(x, a);
	bool v[N];
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= tot; i++) {
		int k = 0;
		for (int j = 1; j <= tot; j++)
			if (i != j) k ^= SG(a[j]);
		v[k] = 1;
	}
	int t = 0;
	while (v[t]) ++t;
	return sg[x] = t;
}

int main() {
	memset(sg, -1, sizeof(sg));
	sg[1] = 0;
	while (cin >> n) {
		int k = 0;
		for (int i = 1; i <= n; i++) {
			int x;
			cin >> x;
			k ^= SG(x);
		}
		puts(k ? "freda" : "rainbow");
	}
	return 0;
}
