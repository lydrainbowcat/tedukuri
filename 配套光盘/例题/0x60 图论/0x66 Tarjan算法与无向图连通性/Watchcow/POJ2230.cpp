#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int head[10010], ver[100010], Next[100010], tot; // 邻接表
int stack[100010], ans[100010]; // 模拟系统栈，答案栈
bool vis[100010];
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
			// vis[i] = vis[i ^ 1] = true;
		}		
		// 与x相连的所有边均已访问，模拟回溯过程，并记录
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