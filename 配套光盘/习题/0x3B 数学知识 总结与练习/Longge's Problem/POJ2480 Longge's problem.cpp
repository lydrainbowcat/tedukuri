//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;

int main() {
	ll n;
	while (cin >> n) {
		ll ans = n;
		for (ll i = 2; i * i <= n; i++)
			if (n % i == 0) {
				int cnt = 1;
				while (n % i == 0) {
					n /= i;
					++cnt;
				}
				ans = ans / i * ((i - 1) * cnt + 1);
			}
		if (n > 1) ans = ans / n * ((n - 1) * 2 + 1);
		cout << ans << endl;
	}
	return 0;
}
