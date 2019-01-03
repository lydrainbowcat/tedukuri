//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006, INF = 0x3f3f3f3f;
int m, n, a[N][N], b[N][N], c[N][N], l[N], r[N];
char s[N];

void Largest_Submatrix() {
	for (int i = 1; i <= m; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= n; j++) {
			if (s[j] == 'a' || s[j] == 'w' || s[j] == 'y' || s[j] == 'z')
				a[i][j] = a[i-1][j] + 1;
			else a[i][j] = 0;
			if (s[j] == 'b' || s[j] == 'w' || s[j] == 'x' || s[j] == 'z')
				b[i][j] = b[i-1][j] + 1;
			else b[i][j] = 0;
			if (s[j] == 'c' || s[j] == 'x' || s[j] == 'y' || s[j] == 'z')
				c[i][j] = c[i-1][j] + 1;
			else c[i][j] = 0;
		}
	}
	int ans = -INF;
	for (int i = 1; i <= m; i++) {
		l[0] = 1;
		r[n+1] = n;
		a[i][0] = a[i][n+1] = -1;
		for (int j = 1; j <= n; j++) {
			l[j] = j;
			while (a[i][l[j]-1] >= a[i][j]) l[j] = l[l[j]-1];
		}
		for (int j = n; j; j--) {
			r[j] = j;
			while (a[i][r[j]+1] >= a[i][j]) r[j] = r[r[j]+1];
		}
		for (int j = 1; j <= n; j++) ans = max(ans, a[i][j] * (r[j] - l[j] + 1));
		l[0] = 1;
		r[n+1] = n;
		b[i][0] = b[i][n+1] = -1;
		for (int j = 1; j <= n; j++) {
			l[j] = j;
			while (b[i][l[j]-1] >= b[i][j]) l[j] = l[l[j]-1];
		}
		for (int j = n; j; j--) {
			r[j] = j;
			while (b[i][r[j]+1] >= b[i][j]) r[j] = r[r[j]+1];
		}
		for (int j = 1; j <= n; j++) ans = max(ans, b[i][j] * (r[j] - l[j] + 1));
		l[0] = 1;
		r[n+1] = n;
		c[i][0] = c[i][n+1] = -1;
		for (int j = 1; j <= n; j++) {
			l[j] = j;
			while (c[i][l[j]-1] >= c[i][j]) l[j] = l[l[j]-1];
		}
		for (int j = n; j; j--) {
			r[j] = j;
			while (c[i][r[j]+1] >= c[i][j]) r[j] = r[r[j]+1];
		}
		for (int j = 1; j <= n; j++) ans = max(ans, c[i][j] * (r[j] - l[j] + 1));
	}
	cout << ans << endl;
}

int main() {
	while (cin >> m >> n) Largest_Submatrix();
	return 0;
}
