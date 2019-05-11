//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2006;
int f[N][N], q[N];

int main() {
	int t, maxp, w;
	cin >> t >> maxp >> w;
	memset(f, 0xcf, sizeof(f));
	int ans = 0;
	for (int i = 1; i <= t; i++) {
		int ap, bp, as, bs;
		scanf("%d %d %d %d", &ap, &bp, &as, &bs);
		for (int j = 0; j <= as; j++) f[i][j] = -1 * j * ap;
		for (int j = 0; j <= maxp; j++) f[i][j] = max(f[i][j], f[i-1][j]);
		if (i <= w) continue;
		int l = 1, r = 0;
		for (int j = 0; j <= maxp; j++) {
			while (l <= r && q[l] < j - as) ++l;
			while (l <= r && f[i-w-1][q[r]] + q[r] * ap <= f[i-w-1][j] + j * ap) --r;
			q[++r] = j;
			if (l <= r) f[i][j] = max(f[i][j], f[i-w-1][q[l]] + (q[l] - j) * ap);
		}
		l = 1, r = 0;
		for (int j = maxp; j >= 0; j--) {
			while (l <= r && q[l] > j + bs) ++l;
			while (l <= r && f[i-w-1][q[r]] + q[r] * bp <= f[i-w-1][j] + j * bp) --r;
			q[++r] = j;
			if (l <= r) f[i][j] = max(f[i][j], f[i-w-1][q[l]] + (q[l] - j) * bp);
		}
	}
	for (int i = 0; i <= maxp; i++) ans = max(ans, f[t][i]);
	cout << ans << endl;
	return 0;
}
