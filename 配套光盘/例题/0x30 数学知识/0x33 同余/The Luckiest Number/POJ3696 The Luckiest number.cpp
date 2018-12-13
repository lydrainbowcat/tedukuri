//Author:XuHt
#include <cmath>
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
ll L, d, k, p, s, i, num = 0;

ll gcd(ll x, ll y) {
	return y ? gcd(y, x % y) : x;
}

ll ksc(ll a, ll b, ll c) {
	ll ans = 0;
	while (b) {
		if (b & 1) ans = (ans + a) % c;
		a = a * 2 % c;
		b >>= 1;
	}
	return ans;
}

ll ksm(ll a, ll b, ll c) {
	ll ans = 1 % c;
	a %= c;
	while (b) {
		if (b & 1) ans = ksc(ans, a, c);
		a = ksc(a, a, c);
		b >>= 1;
	}
	return ans;
}

ll phi(ll n) {
	ll ans = n;
	for (i = 2; i * i <= n; i++)
		if (n % i == 0) {
			ans = ans / i * (i - 1);
			while (n % i == 0) n /= i;
		}
	if (n > 1) ans = ans / n * (n - 1);
	return ans;
}

ll number() {
	d = gcd(L, 8ll);
	k = 9 * L / d;
	if (gcd(k, 10ll) != 1) return 0;
	p = phi(k);
	s = sqrt(p);
	for (i = 1; i <= s; i++)
		if (p % i == 0 && ksm(10ll, i, k) == 1)
			return i;
	for (i = s - 1; i; i--)
		if (p % i == 0 && ksm(10ll, p / i, k) == 1)
			return p / i;
	return 0;
}

int main() {
	while (cin >> L && L)
		printf("Case %lld: %lld\n", ++num, number());
	return 0;
}
