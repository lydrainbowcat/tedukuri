//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006, M = 26, INF = 0x3f3f3f3f;
int n, m, d[N][M], c[M];
bool v[N][M];
queue<pair<int, int> > q;

void spfa(int x, int y) {
	memset(d, 0x3f, sizeof(d));
	q.push(make_pair(x, y));
	d[x][y] = 0;
	v[x][y] = 1;
	while (q.size()) {
		x = q.front().first, y = q.front().second;
		q.pop();
		for (int i = 1; i <= m; i++) {
			int now = x + c[i];
			if (now < 1 || now > n) continue;
			if (d[now][i] > d[x][y] + abs(y - i) + (abs(c[i]) << 1)) {
				d[now][i] = d[x][y] + abs(y - i) + (abs(c[i]) << 1);
				if (!v[now][i]) {
					q.push(make_pair(now, i));
					v[now][i] = 1;
				}
			}
		}
	}
}

int main() {
	cin >> n >> m;
	int w = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &c[i]);
		if (!c[i]) w = i;
	}
	spfa(1, w);
	int ans = INF;
	for (int i = 1; i <= m; i++)
		ans = min(ans, d[n][i]);
	if (ans == INF) puts("-1");
	else cout << ans << endl;
	return 0;
}
