//Author:XuHt
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int N = 500006;
ll a[N], f[N], s[N], h[N];
int n, m, q[N];

void K_Anonymous_Sequence() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) s[i] = s[i-1] + a[i];
	int l = 1, r = 0;
	for (int i = 1; i <= n; i++) {
		h[i-1] = f[i-1] - s[i-1] + (i - 1) * a[i];
		if (i >= m << 1) {
			int j = i - m;
			while (l < r && (h[j] - h[q[r]]) * (a[q[r]+1] - a[q[r-1]+1]) <= (h[q[r]] - h[q[r-1]]) * (a[j+1] - a[q[r]+1])) --r;
			q[++r] = j;
			while (l < r && h[q[l+1]] - h[q[l]] <= i * (a[q[l+1]+1] - a[q[l]+1])) ++l;
			f[i] = f[q[l]] + s[i] - s[q[l]] - a[q[l]+1] * (i - q[l]);
		} else f[i] = f[i-1] + a[i] - a[1];
	}
	cout << f[n] << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) K_Anonymous_Sequence();
	return 0;
}
