//Author:XuHt
#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
priority_queue<pair<ll, ll> > q;

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		ll a;
		scanf("%lld", &a);
		q.push(make_pair(-a, 0));
	}
	while ((n - 1) % (k - 1)) {
		++n;
		q.push(make_pair(0, 0));
	}
	ll ans = 0;
	while (q.size() != 1) {
		ll num = 0, w = 0;
		for (int i = 1; i <= k; i++) {
			num += q.top().first;
			w = min(w, q.top().second);
			q.pop();
		}
		ans += -num;
		q.push(make_pair(num, w - 1));
	}
	cout << ans << endl << -q.top().second << endl;
	return 0;
}
