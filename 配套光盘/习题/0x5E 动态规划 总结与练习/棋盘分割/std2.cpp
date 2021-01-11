//Author:XuHt
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int s[10][10], f[16][10][10][10][10];

int calc(int k, int x1, int y1, int x2, int y2) {
	int ans = INF;
	for (int i = x1 + 1; i < x2; i++) {
		ans = min(ans, f[k-1][x1][y1][i][y2] + f[1][i][y1][x2][y2]);
		ans = min(ans, f[k-1][i][y1][x2][y2] + f[1][x1][y1][i][y2]);
	}
	for (int i = y1 + 1; i < y2; i++) {
		ans = min(ans, f[k-1][x1][y1][x2][i] + f[1][x1][i][x2][y2]);
		ans = min(ans, f[k-1][x1][i][x2][y2] + f[1][x1][y1][x2][i]);
	}
	return ans;
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++) {
			scanf("%d", &s[i][j]);
			s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
		}
	for (int x1 = 0; x1 < 8; x1++)
		for (int y1 = 0; y1 < 8; y1++)
			for (int x2 = x1 + 1; x2 <= 8; x2++)
				for (int y2 = y1 + 1; y2 <= 8; y2++) {
					int p = s[x2][y2] - s[x1][y2] - s[x2][y1] + s[x1][y1];
					f[1][x1][y1][x2][y2] = p * p;
				}
	for (int k = 2; k <= n; k++)
		for (int x1 = 0; x1 < 8; x1++)
			for (int y1 = 0; y1 < 8; y1++)
				for (int x2 = x1 + 1; x2 <= 8; x2++)
					for (int y2 = y1 + 1; y2 <= 8; y2++)
						f[k][x1][y1][x2][y2] = calc(k, x1, y1, x2, y2);
	printf("%.3f\n", sqrt((double)f[n][0][0][8][8] / n - (double)s[8][8] * s[8][8] / n / n));
	return 0;
}
