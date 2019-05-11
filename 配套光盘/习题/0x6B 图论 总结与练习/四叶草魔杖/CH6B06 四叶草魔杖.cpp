//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 16, M = 1 << 16, INF = 0x3f3f3f3f;
int n, m, a[N], s[M], d[M], fa[N], f[M];
struct E {
	int x, y, z;
	bool operator < (const E w) const {
		return z < w.z;
	}
} e[120];

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

inline int work(int w) {
	for (int i = 0; i < n; i++)
		if ((w >> i) & 1) fa[i] = i;
	int ans = 0;
	for (int i = 0; i < m; i++) {
		int x = get(e[i].x), y = get(e[i].y);
		if (x != y && ((w >> e[i].x) & 1) && ((w >> e[i].y) & 1)) {
			fa[x] = y;
			ans += e[i].z;
		}
	}
	int num = -1;
	for (int i = 0; i < n; i++)
		if ((w >> i) & 1) {
			if (num == -1) num = get(i);
			else if (num != get(i)) return INF;
		}
	return ans;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < (1 << n); i++)
		for (int j = 0; j < n; j++)
			if ((i >> j) & 1) s[i] += a[j];
	for (int i = 0; i < m; i++)
		scanf("%d %d %d", &e[i].x, &e[i].y, &e[i].z);
	sort(e, e + m);
	memset(d, 0x3f, sizeof(d));
	for (int i = 1; i < (1 << n); i++)
		if (!s[i]) d[i] = work(i);
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 0; i < (1 << n); i++)
		if (!s[i]) for (int j = 0; j < (1 << n); j++)
			if (!(i & j)) f[i|j] = min(f[i|j], f[j] + d[i]);
	if (f[(1<<n)-1] == INF) puts("Impossible");
	else cout << f[(1<<n)-1] << endl;
	return 0;
}
