//Author:XuHt
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 8006;
int n, a[N], c[N], h[N];

void add(int x) {
	while (x <= n) {
		--c[x];
		x += x & -x;
	}
}

int ask(int x) {
	int ans = 0;
	while (x) {
		ans += c[x];
		x -= x & -x;
	}
	return ans;
}

int main() {
	cin >> n;
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
		int l = 1, r = n;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (ask(mid) < a[i]) l = mid + 1;
			else r = mid;
		}
		add(h[i] = l);
	}
	for (int i = 1; i <= n; i++) printf("%d\n", h[i]);
	return 0;
}
