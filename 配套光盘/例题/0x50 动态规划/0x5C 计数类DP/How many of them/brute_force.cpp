/*
1 0 1
2 0 0
2 1 1
3 0 1
3 1 0
3 2 3
4 0 10
4 1 12
4 2 0
4 3 16
5 0 253
5 1 200
5 2 150
5 3 0
5 4 125
6 0 11968
6 1 7680
6 2 3600
6 3 2160
6 4 0
6 5 1296
7 0 1047613
7 1 506856
7 2 190365
7 3 68600
7 4 36015
7 5 0
7 6 16807
8 0 169181040
8 1 58934848
8 2 16353792
8 3 4695040
8 4 1433600
8 5 688128
8 6 0
8 7 262144
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool a[9][9];
int n, m, ans;
int dfn[9], low[9], num, bridge;

void tarjan(int x, int fa) {
	dfn[x] = low[x] = ++num;
	for(int y=1;y<=n;y++) {
		if (!a[x][y]) continue;
		if (!dfn[y]) {
			tarjan(y, x);
			low[x] = min(low[x], low[y]);
			if (low[y] > dfn[x]) bridge++;
		}
		else if (y != fa)
			low[x] = min(low[x], dfn[y]);
	}
}

int main() {
	cin >> n >> m;
	for (int s = 0; s < 1 << n * (n - 1) / 2; s++) {
		memset(a, 0, sizeof(a));
		int k = 0;
		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n; j++) {
				if (s >> k & 1) a[i][j] = a[j][i] = 1;
				k++;
			}
		memset(dfn, 0, sizeof(dfn));
		bridge = num = 0;
		tarjan(1, 0);
		if (num == n && bridge == m) ans++;
	}
	cout << ans << endl;
}