//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1006, INF = 0x3f3f3f3f;
int n, m, d[N][2], c[N][2];
bool v[N][2];
vector<pair<int, int> > e[N];

inline int Dijkstra(int s, int t) {
	memset(v, 0, sizeof(v));
	memset(d, 0x3f, sizeof(d));
	memset(c, 0, sizeof(c));
	d[s][0] = 0;
	c[s][0] = 1;
	for (int i = 1; i < (n << 1); i++) {
		int now = INF, x = 1, w = 0;
		for (int j = 1; j <= n; j++)
			if (!v[j][0] && d[j][0] < now)
				now = d[x=j][w=0];
			else if (!v[j][1] && d[j][1] < now)
				now = d[x=j][w=1];
		if (now == INF) break;
		v[x][w] = 1;
		for (unsigned int i = 0; i < e[x].size(); i++) {
			int y = e[x][i].first, z = e[x][i].second;
			if (d[y][0] > now + z) {
				d[y][1] = d[y][0];
				c[y][1] = c[y][0];
				d[y][0] = now + z;
				c[y][0] = c[x][w];
			} else if (d[y][0] == now + z)
				c[y][0] += c[x][w];
			else if (d[y][1] > now + z) {
				d[y][1] = now + z;
				c[y][1] = c[x][w];
			} else if (d[y][1] == now + z)
				c[y][1] += c[x][w];
		}
	}
	return c[t][0] + (d[t][1] == d[t][0] + 1 ? c[t][1] : 0);
}

inline void Sightseeing() {
	for (int i = 1; i <= n; i++) e[i].clear();
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x ,&y, &z);
		e[x].push_back(make_pair(y, z));
	}
	int s, t;
	cin >> s >> t;
	cout << Dijkstra(s, t) << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--) Sightseeing();
	return 0;
}
