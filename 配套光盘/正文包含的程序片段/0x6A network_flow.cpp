// 最大流，Edmonds-Karp增广路算法
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int inf = 1 << 29, N = 2010, M = 20010;
int head[N], ver[M], edge[M], Next[M], v[N], incf[N], pre[N];
int n, m, s, t, tot, maxflow;

void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
	ver[++tot] = x, edge[tot] = 0, Next[tot] = head[y], head[y] = tot;
}

bool bfs() {
	memset(v, 0, sizeof(v));
	queue<int> q;
	q.push(s); v[s] = 1;
	incf[s] = inf; // 增广路上各边的最小剩余容量
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = Next[i])
			if (edge[i]) {
				int y = ver[i];
				if (v[y]) continue;
				incf[y] = min(incf[x], edge[i]);
				pre[y] = i; // 记录前驱，便于找到最长路的实际方案
				q.push(y), v[y] = 1;
				if (y == t) return 1;
			}
	}
	return 0;
}

void update() { // 更新增广路及其反向边的剩余容量
	int x = t;
	while (x != s) {
		int i = pre[x];
		edge[i] -= incf[t];
		edge[i ^ 1] += incf[t]; // 利用“成对存储”的xor 1技巧
		x = ver[i ^ 1];
	}
	maxflow += incf[t];
}

int main() {
	while (cin >> m >> n) {
		memset(head, 0, sizeof(head));
		s = 1, t = n;
		tot = 1; maxflow = 0;
		for (int i = 1; i <= m; i++) {
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			add(x, y, c);
		}
		while (bfs()) update();
		cout << maxflow << endl;
	}
}


// 最大流，Dinic算法
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int inf = 1 << 29, N = 50010, M = 300010;
int head[N], ver[M], edge[M], Next[M], d[N], /*当前弧优化*/now[M];
int n, m, s, t, tot, maxflow;
queue<int> q;
void add(int x, int y, int z) {
	ver[++tot]=y, edge[tot]=z, Next[tot]=head[x], head[x]=tot;
	ver[++tot]=x, edge[tot]=0, Next[tot]=head[y], head[y]=tot;
}

bool bfs() { // 在残量网络上构造分层图
	memset(d, 0, sizeof(d));
	while (q.size()) q.pop();
	q.push(s); d[s] = 1; now[s] = head[s];
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = Next[i])
			if (edge[i] && !d[ver[i]]) {
				q.push(ver[i]);
				now[ver[i]] = head[ver[i]];
				d[ver[i]] = d[x] + 1;
				if (ver[i] == t) return 1;
			}
	}
	return 0;
}

int dinic(int x, int flow) { // 在当前分层图上增广
	if (x == t) return flow;
	int rest = flow, k, i;
	for (i = now[x]; i && rest; i = Next[i]) {
		now[x] = i; // 当前弧优化（避免重复遍历从x出发不可扩展的边）
		if (edge[i] && d[ver[i]] == d[x] + 1) {
			k = dinic(ver[i], min(rest, edge[i]));
			if (!k) d[ver[i]] = 0; // 剪枝，去掉增广完毕的点
			edge[i] -= k;
			edge[i ^ 1] += k;
			rest -= k;
		}
	}
	return flow - rest;
}

int main() {
	cin >> n >> m;
	cin >> s >> t; // 源点、汇点
	tot = 1;
	for (int i = 1; i <= m; i++) {
		int x, y, c; scanf("%d%d%d", &x, &y, &c);
		add(x, y, c);
	}
	int flow = 0;
	while (bfs())
		while (flow = dinic(s, inf)) maxflow += flow;
	cout << maxflow << endl;
}

// 费用流，例题：K取方格数 (POJ3422)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int N = 5010, M = 200010;
int ver[M], edge[M], cost[M], Next[M], head[N];
int d[N], incf[N], pre[N], v[N];
int n, k, tot, s, t, maxflow, ans;

void add(int x, int y, int z, int c) {
	// 正向边，初始容量z，单位费用c
	ver[++tot] = y, edge[tot] = z, cost[tot] = c;
	Next[tot] = head[x], head[x] = tot;
	// 反向边，初始容量0，单位费用-c，与正向边“成对存储”
	ver[++tot] = x, edge[tot] = 0, cost[tot] = -c;
	Next[tot] = head[y], head[y] = tot;
}

int num(int i, int j, int k) {
	return (i - 1)*n + j + k*n*n;
}

bool spfa() {
	queue<int> q;
	memset(d, 0xcf, sizeof(d)); // -INF
	memset(v, 0, sizeof(v));
	q.push(s); d[s] = 0; v[s] = 1; // SPFA 求最长路
	incf[s] = 1 << 30; // 增广路上各边的最小剩余容量
	while (q.size()) {
		int x = q.front(); v[x] = 0; q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			if (!edge[i]) continue; // 剩余容量为0，不在残量网络中，不遍历
			int y = ver[i];
			if (d[y]<d[x] + cost[i]) {
				d[y] = d[x] + cost[i];
				incf[y] = min(incf[x], edge[i]);
				pre[y] = i; // 记录前驱，便于找到最长路的实际方案
				if (!v[y]) v[y] = 1, q.push(y);
			}
		}
	}
	if (d[t] == 0xcfcfcfcf) return false; // 汇点不可达，已求出最大流
	return true;
}

// 更新最长增广路及其反向边的剩余容量
void update() {
	int x = t;
	while (x != s) {
		int i = pre[x];
		edge[i] -= incf[t];
		edge[i ^ 1] += incf[t]; // 利用“成对存储”的xor 1技巧
		x = ver[i ^ 1];
	}
	maxflow += incf[t];
	ans += d[t] * incf[t];
}

int main() {
	cin >> n >> k;
	s = 1, t = 2 * n * n;
	tot = 1; // 一会儿要从2开始“成对存储”，2和3是一对，4和5是一对
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int c; scanf("%d", &c);
			add(num(i, j, 0), num(i, j, 1), 1, c);
			add(num(i, j, 0), num(i, j, 1), k - 1, 0);
			if (j<n) add(num(i, j, 1), num(i, j + 1, 0), k, 0);
			if (i<n) add(num(i, j, 1), num(i + 1, j, 0), k, 0);
		}
	while (spfa()) update(); // 计算最大费用最大流
	cout << ans << endl;
}
