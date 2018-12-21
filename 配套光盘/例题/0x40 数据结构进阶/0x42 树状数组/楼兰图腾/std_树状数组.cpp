//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 200006;
int n, a[N], c[N], l[N], r[N];

int ask(int x) {
	int ans = 0;
	while (x) {
		ans += c[x];
		x -= x & -x;
	}
	return ans;
}

void add(int x, int y) {
	while (x <= n) {
		c[x] += y;
		x += x & -x;
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	memset(c, 0, sizeof(c));
	for (int i = n; i; i--) {
		r[i] = ask(a[i] - 1);
		add(a[i], 1);
	}
	memset(c, 0, sizeof(c));
	for (int i = 1; i <= n; i++) {
		l[i] = ask(a[i] - 1);
		add(a[i], 1);
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans += (ll)(n - i - r[i]) * (i - 1 - l[i]);
	cout << ans << " ";
	ans = 0;
	for (int i = 1; i <= n; i++) ans += (ll)r[i] * l[i];
	cout << ans << endl;
	return 0;
}
