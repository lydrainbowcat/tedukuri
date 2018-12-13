//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;
const int N = 26, P = 1000000007;
ll a[N];
int inv[N];

int ksm(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = (ll)ans * a % P;
		a = (ll)a * a % P;
		b >>= 1;
	}
	return ans;
}

int C(ll y, int x) {
	if (y < 0 || x < 0 || y < x) return 0;
	y %= P;
	if (y == 0 || x == 0) return 1;
	int ans = 1;
	for (int i = 0; i < x; i++) ans = (ll)ans * (y - i) % P;
	for (int i = 1; i <= x; i++) ans = (ll)ans * inv[i] % P;
	return ans;
}

int main() {
	for (int i = 1; i <= 20; i++) inv[i] = ksm(i, P - 2);
	int n;
	ll m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	ll ans = C(n + m - 1, n - 1);
	for (int x = 1; x < (1 << n); x++) {
		ll t = n + m;
		int p = 0;
		for (int i = 0; i < n; i++)
			if (x >> i & 1) {
				++p;
				t -= a[i+1];
			}
		t -= p + 1;
		if (p & 1) ans = (ans - C(t, n - 1)) % P;
		else ans = (ans + C(t, n - 1)) % P;
	}
	cout << (ans + P) % P << endl;
	return 0;
}
