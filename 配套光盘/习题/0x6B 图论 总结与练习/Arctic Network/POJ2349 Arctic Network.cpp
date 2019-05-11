//Author:XuHt
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 506;
pair<int, int> p[N];
struct E {
	int x, y, z;
	bool operator < (const E w) const {
		return z < w.z;
	}
} e[N*N];
int n, m, fa[N];

inline int S(int x, int y) {
	int dx = p[x].first - p[y].first;
	int dy = p[x].second - p[y].second;
	return dx * dx + dy * dy;
}

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

inline void Arctic_Network() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		fa[i] = i;
		scanf("%d %d", &p[i].first, &p[i].second);
	}
	int tot = 0;
	for (int i = 1; i <= m; i++)
		for (int j = i + 1; j <= m; j++) {
			e[++tot].x = i;
			e[tot].y = j;
			e[tot].z = S(i, j);
		}
	sort(e + 1, e + tot + 1);
	int cnt = m - n;
	for (int i = 1; i <= tot; i++) {
		int x = get(e[i].x), y = get(e[i].y);
		if (x == y) continue;
		fa[x] = y;
		if (!--cnt) {
			printf("%.2f\n", sqrt(e[i].z));
			return;
		}
	}
}

int main() {
	int t;
	cin >> t;
	while (t--) Arctic_Network();
	return 0;
}
