#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<queue>
#include<cmath>
using namespace std;
#define x first
#define y second
const int SIZE = 2010;
pair<int, int> a[SIZE];
int h, w, n, f[SIZE], mod = 1000000007;
long long jc[200010], jcinv[200010];

int C(int n, int m) {
	return jc[n] * jcinv[m] % mod * jcinv[n - m] % mod;
}

long long power(long long a, int b) {
	long long c = 1;
	for (; b; b >>= 1) {
		if (b & 1) c = c*a%mod;
		a = a*a%mod;
	}
	return c;
}

int main() {
	jc[0] = 1, jcinv[0] = 1;
	for (int i = 1; i <= 200000; i++) {
		jc[i] = jc[i - 1] * i % mod;
		jcinv[i] = power(jc[i], mod - 2);
	}
	cin >> h >> w >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y);
	sort(a + 1, a + n + 1);
	a[n + 1].x = h, a[n + 1].y = w;
	for (int i = 1; i <= n + 1; i++) {
		f[i] = C(a[i].x + a[i].y - 2, a[i].x - 1);
		for (int j = 1; j < i; j++) {
			if (a[j].x > a[i].x || a[j].y > a[i].y) continue;
			f[i] = (f[i] - (long long)f[j] * C(a[i].x + a[i].y - a[j].x - a[j].y, a[i].x - a[j].x)) % mod;
		}
	}
	cout << (f[n + 1] + mod) % mod << endl;
}