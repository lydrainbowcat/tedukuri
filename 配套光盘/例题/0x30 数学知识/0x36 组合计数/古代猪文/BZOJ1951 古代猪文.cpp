//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;
const ll P = 999911659;
ll p[5] = {0,2,3,4679,35617}, m[5] = {0}, t[5];
ll pn[5][35617][2] = {{},{{1,1},{1,1}},{{1,1},{1,1},{2,2}},{{1,1},{1,1}},{{1,1},{1,1}}};
ll x, y;

ll ksm(ll a, ll b, ll c) {
	ll ans = 1;
	a %= c;
	b %= (c - 1);
	while (b) {
		if (b & 1) ans = ans * a % c;
		a = a * a % c;
		b >>= 1;
	}
	return ans;
}

void exgcd(ll a, ll b) {
	if (!b) {
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b);
	ll z = x;
	x = y;
	y = z - (a / b) * y;
}

ll C(ll d, ll n, ll i) {
	if (d < p[i] && n < p[i])
		return pn[i][n][0] * pn[i][d][1] % p[i] * pn[i][n-d][1] % p[i];
	return C(d % p[i], n % p[i], i) * C(d / p[i], n / p[i], i) % p[i];
}

int main() {
	ll n, q;
	cin >> n >> q;
	q %= P;
	if (!q) {
		cout << "0" << endl;
		return 0;
	}
	for (int i = 2; i < 4679; i++) {
		pn[3][i][0] = pn[3][i-1][0] * i % 4679;
		pn[3][i][1] = ksm(pn[3][i][0], 4677, 4679);
	}
	for (int i = 2; i < 35617; i++) {
		pn[4][i][0] = pn[4][i-1][0] * i % 35617;
		pn[4][i][1] = ksm(pn[4][i][0], 35615, 35617);
	}
	for (int i = 1; i <= 4; i++) {
		m[i] = (P - 1) / p[i];
		exgcd(m[i], p[i]);
		t[i] = x;
	}
	ll a[5] = {0,0,0,0,0};
	for (int d = 1; d * d <= n; d++)
		if (n % d == 0)
			for (int i = 1; i <= 4; i++) {
				a[i] = (a[i] + C(d, n, i)) % p[i];
				if (d * d != n) a[i] = (a[i] + C(n/d, n, i)) % p[i];
			}
	ll ans = 0;
	for (int i = 1; i <= 4; i++)
		ans = (a[i] * m[i] % (P - 1) * t[i] % (P - 1) + ans) % (P - 1);
	ans = (ans + P - 1) % (P - 1);
	cout << ksm(q, ans, P) << endl;
	return 0;
}
