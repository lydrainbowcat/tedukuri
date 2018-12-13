//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;
const int P = 9901;
int a, b, m, ans = 1, p[20], c[20];

void divide(int n) {
	m = 0;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) {
			p[++m] = i;
			c[m] = 0;
			while (n % i == 0) {
				n /= i;
				c[m]++;
			}
		}
	if (n > 1) {
		p[++m] = n;
		c[m] = 1;
	}
}

int power(int a, ll b) {
	int c = 1;
	while (b) {
		if (b & 1) c = (ll)c * a % P;
		a = (ll)a * a % P;
		b >>= 1;
	}
	return c;
}

int main() {
	cin >> a >> b;
	divide(a);
	for (int i = 1; i <= m; i++) {
		if ((p[i] - 1) % P == 0) {
			ans = ((ll)b * c[i] + 1) % P * ans % P;
			continue;
		}
		int x = power(p[i], (ll)b * c[i] + 1);
		x = (x - 1 + P) % P;
		int y = p[i] - 1;
		y = power(y, P - 2);
		ans = (ll)ans * x % P * y % P;
	}
	cout << ans << endl;
	return 0;
}
