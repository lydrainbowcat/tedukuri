//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const double INF = 0x3f3f3f3f;
double f[15][15][15][15][5][5];
bool v[15][15][15][15][5][5];
int A, B, C, D;

void add(int x, int &a, int &b, int &c, int &d) {
	switch (x) {
		case 1:
			a++;
			break;
		case 2:
			b++;
			break;
		case 3:
			c++;
			break;
		case 4:
			d++;
			break;
	}
}

double dfs(int a, int b, int c, int d, int x, int y) {
	if (v[a][b][c][d][x][y]) return f[a][b][c][d][x][y];
	v[a][b][c][d][x][y] = 1;
	double &ans = f[a][b][c][d][x][y] = 0;
	int na = a, nb = b, nc = c, nd = d;
	add(x, na, nb, nc, nd);
	add(y, na, nb, nc, nd);
	if (na >= A && nb >= B && nc >= C && nd >= D) return 0;
	int w = 54 - na - nb - nc - nd;
	if (w <= 0) return ans = INF;
	if (a < 13) ans += dfs(a + 1, b, c, d, x, y) * (13 - a) / w;
	if (b < 13) ans += dfs(a, b + 1, c, d, x, y) * (13 - b) / w;
	if (c < 13) ans += dfs(a, b, c + 1, d, x, y) * (13 - c) / w;
	if (d < 13) ans += dfs(a, b, c, d + 1, x, y) * (13 - d) / w;
	if (!x) ans += min(dfs(a, b, c, d, 1, y), min(dfs(a, b, c, d, 2, y), min(dfs(a, b, c, d, 3, y), dfs(a, b, c, d, 4, y)))) / w;
	if (!y) ans += min(dfs(a, b, c, d, x, 1), min(dfs(a, b, c, d, x, 2), min(dfs(a, b, c, d, x, 3), dfs(a, b, c, d, x, 4)))) / w;
	return ++ans;
}

int main() {
	cin >> A >> B >> C >> D;
	double ans = dfs(0, 0, 0, 0, 0, 0);
	if (ans > 100) puts("-1.000");
	else printf("%.3f\n", ans);
	return 0;
}
