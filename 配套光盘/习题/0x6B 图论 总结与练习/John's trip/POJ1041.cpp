#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int head[10010], ver[100010], edge[100010], Next[100010], tot; // 邻接表
int stack[100010], ans[100010]; // 模拟系统栈，答案栈
bool vis[100010];
int deg[100010]; // 节点度数 
int n, m, top, t;

void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}

void euler() {
	stack[++top] = 2; vis[2] = vis[3] = true;
	while (top > 0) {
		int e = stack[top], x = ver[e], i = head[x];
		// 找到一条尚未访问的边
		while (i && vis[i]) i = Next[i];
		// 沿着这条边模拟递归过程，标记该边，并更新表头
		if (i) {
			stack[++top] = i;
			head[x] = Next[i];
			vis[i] = vis[i ^ 1] = true;
		}		
		// 与x相连的所有边均已访问，模拟回溯过程，并记录
		else {
			ans[++t] = edge[stack[top]];
			top--;
		}
	}
}

int main() {
	int x, y, z;
	while (~scanf("%d%d", &x, &y) && x) {
		tot = 1, t = 0, top = 0;
		memset(deg, 0, sizeof(deg));
		memset(head, 0, sizeof(head));
		memset(vis, 0, sizeof(vis));
		do {
			scanf("%d", &z);
			add(x, y, z), add(y, x, z);
			deg[x]++, deg[y]++;
		} while (~scanf("%d%d", &x, &y) && x);
		// 判定欧拉回路是否存在 
		bool flag = false;
		for (int i = 1; i <= 50; i++)
			if (deg[i] & 1) flag = true;
		if (flag) {
			puts("Round trip does not exist.");
			continue;
		}
		euler();
		for (int i = t; i > 1; i--) printf("%d ", ans[i]);
		printf("%d\n", ans[1]);
	}
}
