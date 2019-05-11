//Author:XuHt
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 50006;
int n, a[N], t, p, ans;

void work(int x) {
	int k = a[x] + a[x-1];
	ans += k;
	for (int i = x; i < t - 1; i++) a[i] = a[i+1];
	--t;
	for (p = x - 1; p && a[p-1] < k; p--) a[p] = a[p-1];
	a[p] = k;
	while (p >= 2 && a[p] >= a[p-2]) {
		int d = t - p;
		work(p - 1);
		p = t - d;
	}
}

void An_old_Stone_Game() {
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	t = 1;
	ans = 0;
	for (int i = 1; i < n; i++) {
		a[t++] = a[i];
		while (t >= 3 && a[t-3] <= a[t-1]) work(t - 2);
	}
	while (t > 1) work(t - 1);
	cout << ans << endl;
}

int main() {
	while (cin >> n && n) An_old_Stone_Game();
	return 0;
}
