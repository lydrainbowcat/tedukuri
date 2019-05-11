//Author:XuHt
#include <set>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 100006;
int n, q[N], c[N];
ll m, a[N], f[N];
multiset<ll> s;
multiset<ll>::iterator it;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		if (a[i] > m) {
			puts("-1");
			return 0;
		}
	}
	int t = 1, l = 0, r = 0;
	ll tot = 0;
	for (int i = 1; i <= n; i++) {
		tot += a[i];
		while (tot > m) tot -= a[t++];
		while (l < r && q[l] < t)
			if (++l < r && (it = s.find(f[q[l-1]] + a[q[l]])) != s.end())
				s.erase(it);
		while (l < r && a[q[r-1]] <= a[i])
			if (l < --r && (it = s.find(f[q[r-1]] + a[q[r]])) != s.end())
				s.erase(it);
		if (l < r) s.insert(f[q[r-1]] + a[i]);
		q[r++] = i;
		f[i] = f[t-1] + a[q[l]];
		if (s.begin() != s.end()) f[i] = min(f[i], *s.begin());
	}
	cout << f[n] << endl;
	return 0;
}
