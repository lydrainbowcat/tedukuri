//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;
ll x, y, m, n, l, a, b, g, xx, yy, zz;

void exgcd(ll p, ll q) {
	if (!q) {
		xx = 1;
		yy = 0;
		return;
	}
	exgcd(q, p % q);
	zz = xx;
	xx = yy;
	yy = zz - yy * (p / q);
}

ll gcd(ll p, ll q) {
	return q ? gcd(q, p%q) : p;
}

int main() {
	cin >> x >> y >> m >> n >> l;
	a = m - n;
	b = y - x;
	if (a < 0) {
		a *= -1;
		b *= -1;
	}
	g = gcd(a, l);
	if (b % g) {
		cout << "Impossible" << endl;
		return 0;
	}
	exgcd(a, l);
	ll ans = xx * (b / g);
	cout << (ans % (l / g) + l / g) % (l / g) << endl;
	return 0;
}
