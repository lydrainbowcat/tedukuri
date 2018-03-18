// Kruskal算法，O(mlogm)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct rec { int x, y, z; } edge[500010];
int fa[100010], n, m, ans;
bool operator <(rec a, rec b) {
    return a.z < b.z;
}
int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edge[i].x, &edge[i].y, &edge[i].z);
    // 按照边权排序
    sort(edge + 1, edge + m + 1);
    // 并查集初始化
    for (int i = 1; i <= n; i++) fa[i] = i;
    // 求最小生成树
    for (int i = 1; i <= m; i++) {
        int x = get(edge[i].x);
        int y = get(edge[i].y);
        if (x == y) continue;
        fa[x] = y;
        ans += edge[i].z;
    }
    cout << ans << endl;
}


// Prim算法，O(n^2)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[3010][3010], d[3010];
bool v[3010];
int n, m, ans;

void prim() {
	memset(d, 0x3f, sizeof(d));
	memset(v, 0, sizeof(v));
	d[1] = 0;
	for (int i = 1; i < n; i++) {
		int x = 0;
		for (int j = 1; j <= n; j++)
			if (!v[j] && (x == 0 || d[j] < d[x])) x = j;
		v[x] = 1;
		for (int y = 1; y <= n; y++)
			if (!v[y]) d[y] = min(d[y], a[x][y]);
	}
}

int main() {
	cin >> n >> m;
	// 构建邻接矩阵
	memset(a, 0x3f, sizeof(a));
	for (int i = 1; i <= n; i++) a[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		a[y][x] = a[x][y] = min(a[x][y], z);
	}
	// 求最小生成树
	prim();
    for (int i = 2; i <= n; i++) ans += d[i];
    cout << ans << endl;
}
