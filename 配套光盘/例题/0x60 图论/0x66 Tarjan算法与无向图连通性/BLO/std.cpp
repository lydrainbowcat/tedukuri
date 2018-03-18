#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 100010, M = 500010;
int head[N], ver[M * 2], Next[M * 2];
int dfn[N], low[N], Size[N];
long long ans[N];
bool cut[N];
int n, m, tot, num;

void add(int x, int y) {
	ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	Size[x] = 1;
	int flag = 0, sum = 0;
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if (!dfn[y]) {
			tarjan(y);
			Size[x] += Size[y];
			low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x]) {
				flag++;
				ans[x] += (long long)Size[y] * (n - Size[y]);
				sum += Size[y];
				if (x != 1 || flag > 1) cut[x] = true;
			}
		}
		else low[x] = min(low[x], dfn[y]);
	}
	if (cut[x])
		ans[x] += (long long)(n - sum - 1)*(sum + 1) + (n - 1);
	else
		ans[x] = 2 * (n - 1);
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
	tarjan(1);
	for (int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
}
