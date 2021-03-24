#include <cstdio>
#include <iostream>
using namespace std;
const int N = 106, INF = 0x7fffffff;
int n, m, a[N][N], f[N][N], d[N][N], ans[N];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for (int i = 1; i <= m - n + 1; i++) f[1][i] = a[1][i];
	for (int i = 2; i <= n; i++) {
		int k = -INF, t;
		for (int j = i; j <= m - n + i; j++) {
			if (k < f[i-1][j-1]) {
				k = f[i-1][j-1];
				t = j - 1;
			}
			f[i][j] = k + a[i][j];
			d[i][j] = t;
		}
	}
	int k = -INF, t;
	for (int i = n; i <= m; i++)
		if (k < f[n][i]) {
			k = f[n][i];
			t = i;
		}
	cout << k << endl;
	int w = n;
	while (t) {
		ans[w] = t;
		t = d[w--][t];
	}
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	puts("");
	return 0;
}