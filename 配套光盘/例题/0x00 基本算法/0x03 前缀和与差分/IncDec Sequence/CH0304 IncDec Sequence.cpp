//Author:XuHt
#include <cmath>
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int N = 100006;
ll a[N], b[N];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	b[1] = a[1];
	for (int i = 2; i <= n; i++) b[i] = a[i] - a[i-1];
	ll p = 0, q = 0;
	for (int i = 2; i <= n; i++)
		if (b[i] > 0) p += b[i];
		else if (b[i] < 0) q -= b[i];
	cout << max(p, q) << endl << abs(p - q) + 1 << endl;
	return 0;
}
