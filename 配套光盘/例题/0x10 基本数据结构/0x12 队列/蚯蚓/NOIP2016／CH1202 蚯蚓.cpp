//Author:XuHt
#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, q, u, v, t, delta = 0;
priority_queue<ll> pq;
queue<ll> q1, q2;

int main() {
	cin >> n >> m >> q >> u >> v >> t;
	for (int i = 1; i <= n; i++) {
		ll a;
		scanf("%lld", &a);
		pq.push(a);
	}
	for (int i = 1; i <= m; i++) {
		ll maxx = -INF;
		int w;
		if (pq.size() && maxx < pq.top()) {
			maxx = pq.top();
			w = 0;
		}
		if (q1.size() && maxx < q1.front()) {
			maxx = q1.front();
			w = 1;
		}
		if (q2.size() && maxx < q2.front()) {
			maxx = q2.front();
			w = 2;
		}
		if (w == 1) q1.pop();
		else if (w == 2) q2.pop();
		else pq.pop();
		maxx += delta;
		q1.push(maxx * u / v - delta - q);
		q2.push(maxx - maxx * u / v - delta - q);
		delta += q;
		if (i % t == 0) printf("%lld ", maxx);
	}
	cout << endl;
	for (int i = 1; i <= n + m; i++) {
		ll maxx = -INF;
		int w;
		if (pq.size() && maxx < pq.top()) {
			maxx = pq.top();
			w = 0;
		}
		if (q1.size() && maxx < q1.front()) {
			maxx = q1.front();
			w = 1;
		}
		if (q2.size() && maxx < q2.front()) {
			maxx = q2.front();
			w = 2;
		}
		if (w == 1) q1.pop();
		else if (w == 2) q2.pop();
		else pq.pop();
		if (i % t == 0) printf("%lld ", maxx + delta);
	}
	cout << endl;
	return 0;
}
