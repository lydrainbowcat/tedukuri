//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 5006;
int n, s;
ll f[N], st[N], sc[N];

int main() {
	cin >> n >> s;
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &st[i], &sc[i]);
		st[i] += st[i-1];
		sc[i] += sc[i-1];
	}
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < i; j++)
			f[i] = min(f[i], f[j] + st[i] * (sc[i] - sc[j]) + s * (sc[n] - sc[j]));
	cout << f[n] << endl;
	return 0;
}
