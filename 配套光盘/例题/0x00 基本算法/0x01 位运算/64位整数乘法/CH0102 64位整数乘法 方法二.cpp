//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;

ll mul(ll a, ll b, ll p) {
	a %= p;
	b %= p;
	ll c = (long double)a * b / p;
	ll ans = a * b - c * p;
	return (ans % p + p) % p;
}

int main() {
	ll a, b, p;
	cin >> a >> b >> p;
	cout << mul(a, b, p) << endl;
	return 0;
}
