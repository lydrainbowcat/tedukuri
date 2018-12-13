//Author:XuHt
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 10000006;
ll phi[N];
int v[N], p[N];

int main() {
	int num = 0, n;
	cin >> n;
	memset(phi, 0, sizeof(phi));
	memset(v, 0, sizeof(v));
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!v[i]) {
			v[i] = i;
			p[++num] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= num; j++) {
			if (p[j] > v[i] || p[j] * i > n) break;
			v[p[j]*i] = p[j];
			phi[p[j]*i] = phi[i] * (i % p[j] ? p[j] - 1 : p[j]);
		}
		phi[i] += phi[i-1];
	}
	ll ans = 0;
	for (int i = 1; i <= num; i++) ans += phi[n/p[i]];
	cout << ans * 2 - num << endl;
	return 0;
}
