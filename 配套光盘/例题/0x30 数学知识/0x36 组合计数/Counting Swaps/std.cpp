#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int SIZE = 100010, mod = 1000000009;
int p[SIZE], v[SIZE], T, n;
long long jc[SIZE];

int power(int a, int b) {
	int c = 1;
	for (; b; b >>= 1) {
		if (b & 1) c = (long long)c*a%mod;
		a = (long long)a*a%mod;
	}
	return c;
}

int main()
{
	jc[0] = 1;
	for (int i = 1; i <= 100000; i++) jc[i] = jc[i - 1] * i % mod;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
		for (int i = 1; i <= n; i++) v[i] = 0;
		int cnt = 0;
		long long ans = 1;
		for (int i = 1; i <= n; i++) {
			if (v[i]) continue;
			int len = 1;
			v[i] = 1;
			for (int j = p[i]; j != i; j = p[j]) v[j] = 1, len++;
			cnt++;
			ans = ans * (len == 1 ? 1 : power(len, len - 2)) % mod;
			ans = ans * power(jc[len - 1], mod - 2) % mod;
		}
		ans = ans * jc[n - cnt] % mod;
		cout << ans << endl;
	}
	return 0;
}