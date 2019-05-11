//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;
const int N = 16;
ll m[N], a[N];

ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		x = 1;
		y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, x, y);
	ll z = x;
	x = y;
	y = z - y * (a / b);
	return d;
}

int main() {
	int n;
	cin >> n;
	m[0] = 1;
	for (int i = 1; i <= n; i++) {
		cin >> m[i] >> a[i];
		m[0] *= m[i];
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ll num = m[0] / m[i], x, y;
		exgcd(num, m[i], x, y);
		x %= m[i];
		ans = (ans + a[i] * num * x) % m[0];
	}
	cout << (ans + m[0]) % m[0] << endl;
	return 0;
}
