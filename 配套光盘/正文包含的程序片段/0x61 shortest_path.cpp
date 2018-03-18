// Dijkstra算法，O(n^2)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[3010][3010], d[3010];
bool v[3010];
int n, m;

void dijkstra() {
	memset(d, 0x3f, sizeof(d)); // dist数组
	memset(v, 0, sizeof(v)); // 节点标记
	d[1] = 0;
	for (int i = 1; i < n; i++) { // 重复进行n-1次
		int x = 0;
		// 找到未标记节点中dist最小的
		for (int j = 1; j <= n; j++)
			if (!v[j] && (x == 0 || d[j] < d[x])) x = j;
		v[x] = 1;
		// 用全局最小值点x更新其它节点
		for (int y = 1; y <= n; y++)
			d[y] = min(d[y], d[x] + a[x][y]);
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
		a[x][y] = min(a[x][y], z);
	}
	// 求单源最短路径
	dijkstra();
	for (int i = 1; i <= n; i++)
		printf("%d\n", d[i]);
}


// 堆优化Dijkstra算法，O(mlogn)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 100010, M = 1000010;
int head[N], ver[M], edge[M], Next[M], d[N];
bool v[N];
int n, m, tot;
// 大根堆（优先队列），pair的第二维为节点编号
// pair的第一维为dist的相反数（利用相反数变成小根堆，参见0x71节）
priority_queue< pair<int, int> > q;

void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}

void dijkstra() {
	memset(d, 0x3f, sizeof(d)); // dist数组
	memset(v, 0, sizeof(v)); // 节点标记
	d[1] = 0;
	q.push(make_pair(0, 1));
	while (q.size()) {
		// 取出堆顶
		int x = q.top().second; q.pop();
		if (v[x]) continue;
		v[x] = 1;
		// 扫描所有出边
		for (int i = head[x]; i; i = Next[i]) {
			int y = ver[i], z = edge[i];
			if (d[y] > d[x] + z) {
				// 更新，把新的二元组插入堆
				d[y] = d[x] + z;
				q.push(make_pair(-d[y], y));
			}
		}
	}
}

int main() {
	cin >> n >> m;
	// 构建邻接表
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);
	}
	// 求单源最短路径
	dijkstra();
	for (int i = 1; i <= n; i++)
		printf("%d\n", d[i]);
}


// SPFA算法
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 100010, M = 1000010;
int head[N], ver[M], edge[M], Next[M], d[N];
int n, m, tot;
queue<int> q;
bool v[N];

void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}

void spfa() {
	memset(d, 0x3f, sizeof(d)); // dist数组
	memset(v, 0, sizeof(v)); // 是否在队列中
	d[1] = 0; v[1] = 1;
	q.push(1);
	while (q.size()) {
		// 取出队头
		int x = q.front(); q.pop();
		v[x] = 0;
		// 扫描所有出边
		for (int i = head[x]; i; i = Next[i]) {
			int y = ver[i], z = edge[i];
			if (d[y] > d[x] + z) {
				// 更新，把新的二元组插入堆
				d[y] = d[x] + z;
				if (!v[y]) q.push(y), v[y] = 1;
			}
		}
	}
}

int main() {
	cin >> n >> m;
	// 构建邻接表
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);
	}
	// 求单源最短路径
	spfa();
	for (int i = 1; i <= n; i++)
		printf("%d\n", d[i]);
}


// Floyd算法，(n^3)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int d[310][310];
int n, m;

int main() {
	cin >> n >> m;
	// 把d数组初始化为邻接矩阵
	memset(d, 0x3f, sizeof(d));
	for (int i = 1; i <= n; i++) d[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		d[x][y] = min(d[x][y], z);
	}
	// floyd求任意两点间最短路径
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	// 输出
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) printf("%d ", d[i][j]);
		puts("");
	}
}


// Floyd传递闭包
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
bool d[310][310];
int n, m;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) d[i][i] = 1;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		d[x][y] = d[y][x] = 1;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				d[i][j] |= d[i][k] & d[k][j];
}


// 例题：Floyd求最小环 (POJ1734)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int a[310][310], d[310][310], pos[310][310];
int n, m, ans = 0x3f3f3f3f;
vector<int> path; //具体方案
void get_path(int x, int y) {
	if (pos[x][y] == 0) return;
	get_path(x, pos[x][y]);
	path.push_back(pos[x][y]);
	get_path(pos[x][y], y);
}
int main() {
	cin >> n >> m;
	memset(a, 0x3f, sizeof(a));
	for (int i = 1; i <= n; i++) a[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		a[y][x] = a[x][y] = min(a[x][y], z);
	}
	memcpy(d, a, sizeof(a));
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i < k; i++)
			for (int j = i + 1; j < k; j++)
				if ((long long)d[i][j] + a[j][k] + a[k][i] < ans) {
					ans = d[i][j] + a[j][k] + a[k][i];
					path.clear();
					path.push_back(i);
					get_path(i, j);
					path.push_back(j);
					path.push_back(k);
				}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
					pos[i][j] = k;
				}
	}
	if (ans == 0x3f3f3f3f) {
		puts("No solution.");
		return 0;
	}
	for (int i = 0; i < path.size(); i++)
		printf("%d ", path[i]);
	puts("");
}
