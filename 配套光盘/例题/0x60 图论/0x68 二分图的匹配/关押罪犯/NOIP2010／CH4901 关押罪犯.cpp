//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 20006, M = 200006;
struct P {
	int x, y, z;
	bool operator < (const P w) const {
		return z > w.z;
	}
} p[M];
int n, m, v[N];
vector<pair<int, int> > e[N];

bool dfs(int x, int color) {
	v[x] = color;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i].first;
		if (v[y]) {
			if (v[y] == color) return 0;
		} else {
			if (!dfs(y, 3 - color)) return 0;
		}
	}
	return 1;
}

inline bool pd(int now) {
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1; i <= m; i++) {
		if (p[i].z <= now) break;
		e[p[i].x].push_back(make_pair(p[i].y, p[i].z));
		e[p[i].y].push_back(make_pair(p[i].x, p[i].z));
	}
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= n; i++)
		if (!v[i] && !dfs(i, 1)) return 0;
	return 1;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].z);
	sort(p + 1, p + m + 1);
	int l = 0, r = p[1].z;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (pd(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;
	return 0;
}
