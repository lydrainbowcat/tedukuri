#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int ver[200002], edge[200002], next[200002], head[100002];
int out[100002], deg[100002];
int n, m, tot;
double dis[100002];
queue<int> q;

void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, next[tot] = head[x], head[x] = tot;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(y, x, z); // 建反图
		deg[x]++; out[x]++;
	}
	q.push(n); 
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = next[i]) {
			int y = ver[i];
			dis[y] += (dis[x] + edge[i]) / deg[y];
			out[y]--;
			if (out[y] == 0) q.push(y);
		}
	}
	printf("%.2f\n", dis[1]);
}