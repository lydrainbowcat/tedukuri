//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2006, V = 306, INF = 0x3f3f3f3f;
int n, m, v, e, c[N], d[N], s[V][V];
double k[N], f[N][N][2];

int main() {
	cin >> n >> m >> v >> e;
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
	for (int i = 1; i <= n; i++) scanf("%lf", &k[i]);
	for (int i = 1; i <= v; i++)
		for (int j = 1; j < i; j++)
			s[j][i] = s[i][j] = INF;
	for (int i = 1; i <= e; i++) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		s[b][a] = s[a][b] = min(s[a][b], w);
	}
	for (int x = 1; x <= v; x++)
		for (int i = 1; i <= v; i++)
			for (int j = 1; j < i; j++)
				s[j][i] = s[i][j] = min(s[i][j], s[i][x] + s[x][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++)
			f[i][j][0] = f[i][j][1] = INF;
	f[1][0][0] = f[1][1][1] = 0;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j <= m; j++) {
			f[i][j][0] = min(f[i-1][j][1] + k[i-1] * s[d[i-1]][c[i]] + (1 - k[i-1]) * s[c[i-1]][c[i]], f[i-1][j][0] + s[c[i-1]][c[i]]);
			if (j) f[i][j][1] = min(f[i-1][j-1][1] + k[i-1] * k[i] * s[d[i-1]][d[i]] + k[i-1] * (1 - k[i]) * s[d[i-1]][c[i]] + (1 - k[i-1]) * k[i] * s[c[i-1]][d[i]] + (1 - k[i-1]) * (1 - k[i]) * s[c[i-1]][c[i]], f[i-1][j-1][0] + k[i] * s[c[i-1]][d[i]] + (1 - k[i]) * s[c[i-1]][c[i]]);
		}
	double ans = INF;
	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= 1; j++)
			ans = min(ans, f[n][i][j]);
	printf("%.2lf\n", ans);
	return 0;
}
