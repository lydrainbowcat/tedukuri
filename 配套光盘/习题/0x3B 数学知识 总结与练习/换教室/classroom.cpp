#include <iostream>
#include <cstdio>
#include <cstring>
#define maxn 2010
#define maxv 310
#define INF 1000000007
using namespace std;

int n, m, v, e;
int c[maxn], d[maxn];
double k[maxn], dis[maxv][maxv], f[maxn][maxn][2];

inline void init()
{
    for (register int i = 0; i < maxv; ++i)
        for (register int j = 0; j < maxv; ++j)
            if (i == j) dis[i][j] = 0;
            else dis[i][j] = INF;
    for (register int i = 0; i < maxn; ++i)
        for (register int j = 0; j < maxn; ++j)
            f[i][j][0] = f[i][j][1] = INF;
    f[1][0][0] = 0, f[1][1][1] = 0;
}

inline void floyed()
{
	for (register int k = 1; k <= v; ++k)
		for (register int i = 1; i <= v; ++i)
			for (register int j = 1; j <= v; ++j)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &v, &e);
	for (register int i = 1; i <= n; ++i) scanf("%d", &c[i]);
	for (register int i = 1; i <= n; ++i) scanf("%d", &d[i]);
	for (register int i = 1; i <= n; ++i) scanf("%lf", &k[i]);
	init();
	for (register int i = 1; i <= e; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		if (w < dis[x][y]) dis[x][y] = w;
		dis[y][x] = dis[x][y];
	}
	floyed();
	for (register int i = 2; i <= n; ++i) {
		f[i][0][0] = f[i-1][0][0] + dis[c[i-1]][c[i]];
		for (register int j = 1; j <= min(i, m); ++j) {
			f[i][j][0] = min(f[i-1][j][0] + dis[c[i-1]][c[i]], f[i-1][j][1] + (1 - k[i-1]) * dis[c[i-1]][c[i]] + k[i-1] * dis[d[i-1]][c[i]]);
			f[i][j][1] = min(f[i-1][j-1][0] + k[i] * dis[c[i-1]][d[i]] + (1 - k[i]) * dis[c[i-1]][c[i]], f[i-1][j-1][1] + k[i-1] * k[i] * dis[d[i-1]][d[i]] + (1 - k[i-1]) * k[i] * dis[c[i-1]][d[i]] + k[i-1] * (1 - k[i]) * dis[d[i-1]][c[i]] + (1 - k[i-1]) * (1 - k[i]) * dis[c[i-1]][c[i]]);
		}
	}
	double ans(f[n][0][0]);
	for (register int i = 1; i <= m; ++i) ans = min(ans, min(f[n][i][0], f[n][i][1]));
	printf("%.2lf", ans);
	return 0;
}