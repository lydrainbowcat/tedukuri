//Author:XuHt
#include <iostream>
#define ll long long
using namespace std;
const ll INF = 0x7fffffff;
ll n, p[11] = {0,2,3,5,7,11,13,17,19,23,29}, c[11];
ll ans = INF, cnt = 1;

void dfs(ll now, ll num, ll cnt0) {
	if (now == 11) {
		if (cnt0 > cnt || (cnt0 == cnt && ans > num)) {
			cnt = cnt0;
			ans = num;
		}
		return;
	}
	ll num0 = num;
	for (int i = 0; i <= c[now-1]; i++) {
		if (num0 > n) return;
		c[now] = i;
		dfs(now + 1, num0, cnt0 * (i + 1));
		num0 *= p[now];
	}
}

int main() {
	cin >> n;
	c[0] = INF;
	dfs(1, 1, 1);
	cout << ans << endl;
	return 0;
}
