//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;

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
	while (cin >> n) {
		ll a, b, x, y, k;
		cin >> a >> b;
		ll lcm = a, ans = b;
		bool flag = 1;
		--n;
		while (n--) {
			cin >> a >> b;
			b = (b - ans % a + a) % a;
			ll d = exgcd(lcm, a, x, y);
			if (b % d) flag = 0;
			else k = x * (b / d) % a;
			ans += k * lcm;
			lcm = lcm / d * a;
			ans = (ans % lcm + lcm) % lcm;
		}
		if (flag) cout << ans << endl;
		else cout << "-1" << endl;
	}
	return 0;
}
