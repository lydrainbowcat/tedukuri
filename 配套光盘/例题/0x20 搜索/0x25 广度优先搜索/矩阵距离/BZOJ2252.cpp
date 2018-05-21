#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int dx[4] = { -1,1,0,0 }, dy[4] = { 0,0,-1,1 };
char s[1020][1020];
int d[1020][1020], n, m;
queue<pair<int, int>> q;
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	memset(d, -1, sizeof(d));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] == '1') q.push(make_pair(i, j)), d[i][j] = 0;
	while (q.size()) {
		pair<int, int> now = q.front();
		q.pop();
		for (int k = 0; k < 4; k++) {
			pair<int, int> next(now.first + dx[k], now.second + dy[k]);
			if (next.first<1 || next.second<1 || next.first>n || next.second>m) continue;
			if (d[next.first][next.second] == -1) {
				d[next.first][next.second] = d[now.first][now.second] + 1;
				q.push(next);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) printf("%d ", d[i][j]);
		puts("");
	}
}
