//Author:XuHt
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006, C = 106;
int n, m, p[N], d[N][C];
bool v[N][C];
vector<pair<int, int> > e[N];
priority_queue<pair<int, pair<int, int> > > q;

void Full_Tank() {
	int c, st, ed;
	scanf("%d %d %d", &c, &st, &ed);
	priority_queue<pair<int, pair<int, int> > > empty;
	swap(q, empty);
	memset(d, 0x3f, sizeof(d));
	q.push(make_pair(0, make_pair(st, 0)));
	d[st][0] = 0;
	memset(v, 0, sizeof(v));
	while (q.size()) {
		int city = q.top().second.first;
		int fuel = q.top().second.second;
		q.pop();
		if (city == ed) {
			cout << d[city][fuel] << endl;
			return;
		}
		if (v[city][fuel]) continue;
		v[city][fuel] = 1;
		if (fuel < c && d[city][fuel+1] > d[city][fuel] + p[city]) {
			d[city][fuel+1] = d[city][fuel] + p[city];
			q.push(make_pair(-d[city][fuel] - p[city], make_pair(city, fuel + 1)));
		}
		for (unsigned int i = 0; i < e[city].size(); i++) {
			int y = e[city][i].first, z = e[city][i].second;
			if (z <= fuel && d[y][fuel-z] > d[city][fuel]) {
				d[y][fuel-z] = d[city][fuel];
				q.push(make_pair(-d[city][fuel], make_pair(y, fuel - z)));
			}
		}
	}
	cout << "impossible" << endl;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) scanf("%d", &p[i]);
	for (int i = 1; i <= m; i++) {
		int u, v, d;
		scanf("%d %d %d", &u, &v, &d);
		e[u].push_back(make_pair(v, d));
		e[v].push_back(make_pair(u, d));
	}
	int q;
	cin >> q;
	while (q--) Full_Tank();
	return 0;
}
