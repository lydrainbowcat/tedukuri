//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;

int power(int a, int b, int p) {
	int ans = 1 % p;
	while (b) {
		if (b & 1) ans = (ll)ans * a % p;
		a = (ll)a * a % p;
		b >>= 1;
	}
	return ans;
}

void Raising_Modulo_Numbers() {
	int p, n;
	cin >> p >> n;
	int ans = 0;
	while (n--) {
		int a, b;
		cin >> a >> b;
		ans = (ll)(ans + power(a, b, p)) % p;
	}
	cout << ans << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) Raising_Modulo_Numbers();
	return 0;
}
