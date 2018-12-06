#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<queue>
using namespace std;
int n, m, deg[30010], a[30010];
int ver[30010], Next[30010], head[30010], tot, cnt;
bitset<30010> f[30010];

void add(int x, int y) { // 在邻接表中添加一条有向边
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
	deg[y]++;
}

void topsort() { // 拓扑排序
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (deg[i] == 0) q.push(i);
	while (q.size()) {
		int x = q.front(); q.pop();
		a[++cnt] = x;
		for (int i = head[x]; i; i = Next[i]) {
			int y = ver[i];
			if (--deg[y] == 0) q.push(y);
		}
	}
}

void calc() {
	for (int i = cnt; i; i--) {
		int x = a[i];
		f[x][x] = 1;
		for (int i = head[x]; i; i = Next[i]) {
			int y = ver[i];
			f[x] |= f[y];
		}
	}
}

int main() {
	cin >> n >> m; // 点数、边数
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	topsort();
	calc();
	for (int i = 1; i <= n; i++) printf("%d\n", f[i].count());
}
