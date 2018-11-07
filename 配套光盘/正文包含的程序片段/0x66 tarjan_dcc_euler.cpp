// tarjan算法求无向图的桥、边双连通分量并缩点
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int SIZE = 100010;
int head[SIZE], ver[SIZE * 2], Next[SIZE * 2];
int dfn[SIZE], low[SIZE], c[SIZE];
int n, m, tot, num, dcc, tc;
bool bridge[SIZE * 2];
int hc[SIZE], vc[SIZE * 2], nc[SIZE * 2];

void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void add_c(int x, int y) {
	vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

void tarjan(int x, int in_edge) {
	dfn[x] = low[x] = ++num;
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y, i);
			low[x] = min(low[x], low[y]);
			if (low[y] > dfn[x])
				bridge[i] = bridge[i ^ 1] = true;
		}
		else if (i != (in_edge ^ 1))
			low[x] = min(low[x], dfn[y]);
	}
}

void dfs(int x) {
	c[x] = dcc;
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (c[y] || bridge[i]) continue;
		dfs(y);
	}
}

int main() {
	cin >> n >> m;
	tot = 1;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i, 0);
	for (int i = 2; i < tot; i += 2)
		if (bridge[i])
			printf("%d %d\n", ver[i ^ 1], ver[i]);

	for (int i = 1; i <= n; i++)
		if (!c[i]) {
			++dcc;
			dfs(i);
		}
	printf("There are %d e-DCCs.\n", dcc);
	for (int i = 1; i <= n; i++)
		printf("%d belongs to DCC %d.\n", i, c[i]);

	tc = 1;
	for (int i = 2; i <= tot; i++) {
		int x = ver[i ^ 1], y = ver[i];
		if (c[x] == c[y]) continue;
		add_c(c[x], c[y]);
	}
	printf("缩点之后的森林，点数 %d，边数 %d\n", dcc, tc / 2);
	for (int i = 2; i < tc; i += 2)
		printf("%d %d\n", vc[i ^ 1], vc[i]);
}


// tarjan算法求无向图的割点、点双连通分量并缩点
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int SIZE = 100010;
int head[SIZE], ver[SIZE * 2], Next[SIZE * 2];
int dfn[SIZE], low[SIZE], stack[SIZE], new_id[SIZE], c[SIZE];
int n, m, tot, num, root, top, cnt, tc;
bool cut[SIZE];
vector<int> dcc[SIZE];
int hc[SIZE], vc[SIZE * 2], nc[SIZE * 2];

void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void add_c(int x, int y) {
	vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	stack[++top] = x;
	if (x == root && head[x] == 0) { // 孤立点
		dcc[++cnt].push_back(x);
		return;
	}
	int flag = 0;
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x]) {
				flag++;
				if (x != root || flag > 1) cut[x] = true;
				cnt++;
				int z;
				do {
					z = stack[top--];
					dcc[cnt].push_back(z);
				} while (z != y);
				dcc[cnt].push_back(x);
			}
		}
		else low[x] = min(low[x], dfn[y]);
	}
}

int main() {
	cin >> n >> m;
	tot = 1;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (x == y) continue;
		add(x, y), add(y, x);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) root = i, tarjan(i);
	for (int i = 1; i <= n; i++)
		if (cut[i]) printf("%d ", i);
	puts("are cut-vertexes");
	for (int i = 1; i <= cnt; i++) {
		printf("v-DCC #%d:", i);
		for (int j = 0; j < dcc[i].size(); j++)
			printf(" %d", dcc[i][j]);
		puts("");
	}
	// 给每个割点一个新的编号(编号从cnt+1开始)
	num = cnt;
	for (int i = 1; i <= n; i++)
		if (cut[i]) new_id[i] = ++num;
	// 建新图，从每个v-DCC到它包含的所有割点连边
	tc = 1;
	for (int i = 1; i <= cnt; i++)
		for (int j = 0; j < dcc[i].size(); j++) {
			int x = dcc[i][j];
			if (cut[x]) {
				add_c(i, new_id[x]);
				add_c(new_id[x], i);
			}
			else c[x] = i; // 除割点外，其它点仅属于1个v-DCC
		}
	printf("缩点之后的森林，点数 %d，边数 %d\n", num, tc / 2);
	printf("编号 1~%d 的为原图的v-DCC，编号 >%d 的为原图割点\n", cnt, cnt);
	for (int i = 2; i < tc; i += 2)
		printf("%d %d\n", vc[i ^ 1], vc[i]);
}


// 求出欧拉图中的一条欧拉回路
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int head[100010], ver[1000010], Next[1000010], tot; // 邻接表
int stack[1000010], ans[1000010]; // 模拟系统栈，答案栈
bool vis[1000010];
int n, m, top, t;

void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void euler() {
	stack[++top] = 1;
	while (top > 0) {
		int x = stack[top], i = head[x];
		// 找到一条尚未访问的边
		while (i && vis[i]) i = Next[i];
		// 沿着这条边模拟递归过程，标记该边，并更新表头
		if (i) {
			stack[++top] = ver[i];
			head[x] = Next[i];
			vis[i] = vis[i ^ 1] = true;
		}		
		// 与x相连的所有边均已访问，模拟回溯过程，并记录于答案栈中
		else {
			top--;
			ans[++t] = x;
		}
	}
}

int main() {
	cin >> n >> m;
	tot = 1;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	euler();
	for (int i = t; i; i--) printf("%d\n", ans[i]);
}
