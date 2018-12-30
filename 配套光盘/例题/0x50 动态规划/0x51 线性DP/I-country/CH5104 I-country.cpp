//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#define _f f[i][j][l][r][x][y]
#define _cl cl[i][j][l][r][x][y]
#define _cr cr[i][j][l][r][x][y]
#define _dx dx[i][j][l][r][x][y]
#define _dy dy[i][j][l][r][x][y]
using namespace std;
const int N = 16, K = 226;
int n, m, k, f[N][K][N][N][2][2], a[N][N], b[N][N];
int cl[N][K][N][N][2][2], cr[N][K][N][N][2][2];
int dx[N][K][N][N][2][2], dy[N][K][N][N][2][2];

inline void work(int i, int j, int l, int r, int x, int y, int w, int L, int R, int X, int Y) {
	if (w < _f) return;
	_f = w;
	_cl = L;
	_cr = R;
	_dx = X;
	_dy = Y;
}

void print(int i, int j, int l, int r, int x, int y) {
	if (!j) return;
	print(i - 1, j - (r - l + 1), _cl, _cr, _dx, _dy);
	for (j = l; j <= r; j++) printf("%d %d\n", i, j);
}

int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			b[i][j] = b[i][j-1] + a[i][j];
		}
	memset(f, 0xcf, sizeof(f));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			for (int l = 1; l <= m; l++)
				for (int r = l; r <= m; r++) {
					if (r - l + 1 > j) break;
					int w = b[i][r] - b[i][l-1];
					for (int x = 0; x < 2; x++)
						for (int y = 0; y < 2; y++)
							work(i, j, l, r, x, y, w, m, 0, x, y);
					for (int p = l; p <= r; p++)
						for (int q = p; q <= r; q++)
							work(i, j, l, r, 1, 1, f[i-1][j-(r-l+1)][p][q][1][1] + w, p, q, 1, 1);
					for (int p = 1; p <= l; p++)
						for (int q = r; q <= m; q++) {
							work(i, j, l, r, 0, 0, f[i-1][j-(r-l+1)][p][q][0][0] + w, p, q, 0, 0);
							work(i, j, l, r, 0, 0, f[i-1][j-(r-l+1)][p][q][1][0] + w, p, q, 1, 0);
							work(i, j, l, r, 0, 0, f[i-1][j-(r-l+1)][p][q][0][1] + w, p, q, 0, 1);
							work(i, j, l, r, 0, 0, f[i-1][j-(r-l+1)][p][q][1][1] + w, p, q, 1, 1);
						}
					for (int p = l; p <= r; p++)
						for (int q = r; q <= m; q++) {
							work(i, j, l, r, 1, 0, f[i-1][j-(r-l+1)][p][q][1][0] + w, p, q, 1, 0);
							work(i, j, l, r, 1, 0, f[i-1][j-(r-l+1)][p][q][1][1] + w, p, q, 1, 1);
						}
					for (int p = 1; p <= l; p++)
						for (int q = l; q <= r; q++) {
							work(i, j, l, r, 0, 1, f[i-1][j-(r-l+1)][p][q][0][1] + w, p, q, 0, 1);
							work(i, j, l, r, 0, 1, f[i-1][j-(r-l+1)][p][q][1][1] + w, p, q, 1, 1);
						}
				}
	int ans = 0, ai, al, ar, ax, ay;
	for (int i = 1; i <= n; i++)
		for (int l = 1; l <= m; l++)
			for (int r = l; r <= m; r++)
				for (int x = 0; x < 2; x++)
					for (int y = 0; y < 2; y++)
						if (ans < f[i][k][l][r][x][y]) {
							ans = f[i][k][l][r][x][y];
							ai = i;
							al = l;
							ar = r;
							ax = x;
							ay = y;
						}
	printf("Oil : %d\n", ans);
	print(ai, k, al, ar, ax, ay);
	return 0;
}
