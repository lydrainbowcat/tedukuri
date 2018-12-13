//Author:XuHt
#include <iostream>
#include <algorithm>
using namespace std;
const int P = 10007;
int x, y, inv[1001];

int exgcd(int a, int b) {
	if (!b) {
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b, a%b);
	int z = x;
	x = y;
	y = z - y * (a / b);
	return d;
}

int main() {
	for (int i = 1; i <= 1000; i++) {
		exgcd(i, P);
		inv[i] = x;
	}
	int a, b, k, n, m;
	cin >> a >> b >> k >> n >> m;
	int ans = 1;
	a %= P;
	b %= P;
	n = min(m, n);
	for (int i = 1; i <= n; i++)
		ans = (ans * inv[i] % P * (k + 1 - i)) % P;
	for (int i = 1; i <= n; i++) ans = ans * a % P;
	for (int i = 1; i <= m; i++) ans = ans * b % P;
	cout << (ans % P + P) % P << endl;
	return 0;
}
