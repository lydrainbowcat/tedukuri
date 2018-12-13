//Author:XuHt
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int N = 1000001;
const ll P = 1000000007;
ll num[N], inv[N], f[N];

ll ksm(ll x, int k) {
	ll ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % P;
		x = x * x % P;
		k >>= 1;
	}
	return ans;
}

int main() {
	num[0] = 1;
	for (int i = 1; i < N; i++)
		num[i] = num[i-1] * i % P;
	inv[N-1] = ksm(num[N-1], P - 2);
	for (int i = N - 2; i >= 0; i--)
		inv[i] = inv[i+1] * (i + 1) % P;
	f[0] = 1;
	f[1] = 0;
	for (int i = 2; i < N; i++)
		f[i] = (f[i-1] + f[i-2]) % P * (i - 1) % P;
	int t, n, m;
	cin >> t;
	while (t--) {
		scanf("%d %d", &n, &m);
		printf("%lld\n", num[n] * inv[n-m] % P * inv[m] % P * f[n-m] % P);
	}
	return 0;
}
