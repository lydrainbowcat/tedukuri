//Author:XuHt
//POJ3074
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int a[9][9], p[9][9], num = 0;
int cnt[1<<9], f[1<<9], ans = 0;
int x[9], y[9], z[9];

void work(int i, int j, int k) {
	x[i] ^= (1 << k);
	y[j] ^= (1 << k);
	z[i/3*3+j/3] ^= (1 << k);
}

void dfs(int num) {
	if (!num) {
		int ans0 = 0;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				ans0 += a[i][j] * p[i][j];
		ans = max(ans, ans0);
		return;
	}
	int k = 10, ti, tj;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (!a[i][j]) {
				int w = x[i] & y[j] & z[i/3*3+j/3];
				if (cnt[w] < k) {
					k = cnt[w];
					ti = i;
					tj = j;
				}
			}
	int w = x[ti] & y[tj] & z[ti/3*3+tj/3];
	while (w) {
		int now = f[w&-w];
		a[ti][tj] = now + 1;
		work(ti, tj, now);
		dfs(num - 1);
		work(ti, tj, now);
		a[ti][tj] = 0;
		w -= w & -w;
	}
}

int main() {
	cnt[0] = 0;
	for (int i = 1; i < (1 << 9); i++) cnt[i] = cnt[i-(i&-i)] + 1;
	for (int i = 0; i < 9; i++) {
		f[1<<i] = i;
		x[i] = y[i] = z[i] = (1 << 9) - 1;
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			cin >> a[i][j];
			if (a[i][j]) work(i, j, a[i][j] - 1);
			else ++num;
			if (i == 4 && j == 4) p[i][j] = 10;
			else if (i >= 3 && i <= 5 && j >= 3 && j <= 5) p[i][j] = 9;
			else if (i >= 2 && i <= 6 && j >= 2 && j <= 6) p[i][j] = 8;
			else if (i >= 1 && i <= 7 && j >= 1 && j <= 7) p[i][j] = 7;
			else p[i][j] = 6;
		}
	dfs(num);
	if (ans == 0) cout << "-1" << endl;
	else cout << ans << endl;
	return 0;
}
