//Author:xht37
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 4e3 + 6;
int n, b[N], c[N], cnt, p[N][N];
vector<int> a[N], e[N], ans[N];
int dfn[N], low[N], num;
int st[N], top, ins[N];

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	st[++top] = x;
	ins[x] = 1;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (ins[y])
			low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x]) {
		++cnt;
		int y;
		do {
			y = st[top--];
			ins[y] = 0;
			c[y] = cnt;
		} while (x != y);
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int k;
		scanf("%d", &k);
		while (k--) {
			int x;
			scanf("%d", &x);
			a[i].push_back(x);
			p[i][x] = 1;
		}
	}
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for (int x = 1; x <= n; x++)
		for (unsigned int i = 0; i < a[x].size(); i++) {
			int y = a[x][i];
			if (y == b[x]) e[y+n].push_back(x);
			else e[x].push_back(y + n);
		}
	for (int i = 1; i <= n << 1; i++)
		if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			if (b[i] == j || (p[i][j] && c[i] == c[j+n]))
				ans[i].push_back(j);
		printf("%d", (int)ans[i].size());
		for (unsigned int j = 0; j < ans[i].size(); j++)
			printf(" %d", ans[i][j]);
		puts("");
	}
	return 0;
}
