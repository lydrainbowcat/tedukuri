//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 10001;
ll x[N];
int n, a[N], cnt[N], p[N], tot;

void work(int n) {
	tot = 0;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) {
			p[tot++]=i;
			while (n % i == 0) n /= i;
		}
	if (n > 1) p[tot++] = n;
	for (int i = 1; i < (1 << tot); i++) {
		int t = 1, num = 0;
		for (int j = 0; j < tot; j++)
			if ((i >> j) & 1) {
				t *= p[j];
				++num;
			}
		++cnt[t];
		a[t] = num;
	}
}

int main() {
	for (int i = 4; i < N; i++)
		x[i] = (ll)i * (i - 1) * (i - 2) * (i - 3) / 24;
	memset(a, 0, sizeof(a));
	while (cin >> n) {
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++) {
			int w;
			scanf("%d", &w);
			work(w);
		}
		ll ans = 0;
		for (int i = 2; i < N; i++)
			if (cnt[i] > 3) {
				if (a[i] & 1) ans += x[cnt[i]];
				else ans -= x[cnt[i]];
			}
		cout << x[n] - ans << endl;
	}
	return 0;
}
