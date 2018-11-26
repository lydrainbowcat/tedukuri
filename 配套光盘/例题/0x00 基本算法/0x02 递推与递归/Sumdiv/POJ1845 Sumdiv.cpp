//Author:XuHt
#include <vector>
#include <iostream>
#define ll long long
using namespace std;
const ll P = 9901;
vector<pair<ll, ll> > w;

ll ksm(ll a, ll b) {
	ll ans = 1;
	a %= P;
	while (b) {
		if (b & 1) (ans *= a) %= P;
		(a *= a) %= P;
		b >>= 1;
	}
	return ans;
}

ll get_sum(ll p, ll c) {
	if (!p) return 0;
	if (!c) return 1;
	if (c & 1) return (ksm(p, (c + 1) / 2) + 1) * get_sum(p, c / 2) % P;
	return ((ksm(p, c / 2) + 1) * get_sum(p, c / 2 - 1) + ksm(p, c)) % P;
}

void fj(ll a) {
	for (ll i = 2; i * i <= a; i++)
		if (!(a % i)) {
			ll num = 0;
			while (!(a % i)) {
				num++;
				a /= i;
			}
			w.push_back(make_pair(i, num));
		}
	if (a != 1) w.push_back(make_pair(a, 1));
}

int main() {
	ll a, b;
	cin >> a >> b;
	fj(a);
	ll ans = 1;
	for (unsigned ll i = 0; i < w.size(); i++) {
		ll p = w[i].first, c = w[i].second;
		(ans *= get_sum(p, b * c)) %= P;
	}
	cout << ans << endl;
	return 0;
}
