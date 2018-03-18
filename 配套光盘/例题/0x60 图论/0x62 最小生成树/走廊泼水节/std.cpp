#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct rec { int x, y, z; } edge[6010];
int fa[6010], s[6010], n, T;
long long ans;
bool operator <(rec a, rec b) {
	return a.z < b.z;
}
int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}
int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i < n; i++)
			scanf("%d%d%d", &edge[i].x, &edge[i].y, &edge[i].z);
		sort(edge + 1, edge + n);
		for (int i = 1; i <= n; i++)
			fa[i] = i, s[i] = 1;
		ans = 0;
		for (int i = 1; i < n; i++) {
			int x = get(edge[i].x);
			int y = get(edge[i].y);
			if (x == y) continue;
			ans += (long long)(edge[i].z + 1) * (s[x] * s[y] - 1);
			fa[x] = y;
			s[y] += s[x];
		}
		cout << ans << endl;
	}
}
