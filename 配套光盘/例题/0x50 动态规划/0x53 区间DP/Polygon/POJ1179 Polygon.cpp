//Author:XuHt
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106, INF = 0x3f3f3f3f;
char c[N];
int a[N], fmax[N][N], fmin[N][N];
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
		cin >> a[i];
	}
	for (int i = n + 1; i <= (n << 1); i++) {
		c[i] = c[i-n];
		a[i] = a[i-n];
	}
	memset(fmax, 0xcf, sizeof(fmax));
	memset(fmin, 0x3f, sizeof(fmin));
	for (int i = 1; i <= (n << 1); i++) fmax[i][i] = fmin[i][i] = a[i];
	for (int len = 2; len <= n; len++)
		for (int l = 1; l + len - 1 <= (n << 1); l++) {
			int r = l + len - 1;
			for (int k = l + 1; k <= r; k++)
				if (c[k] == 't') {
					fmax[l][r] = max(fmax[l][r], fmax[l][k-1] + fmax[k][r]);
					fmin[l][r] = min(fmin[l][r], fmin[l][k-1] + fmin[k][r]);
				} else {
					fmax[l][r] = max(fmax[l][r], max(fmax[l][k-1] * fmax[k][r], fmin[l][k-1] * fmin[k][r]));
					fmin[l][r] = min(fmin[l][r], min(fmax[l][k-1] * fmax[k][r], min(fmin[l][k-1] * fmin[k][r], min(fmax[l][k-1] * fmin[k][r], fmin[l][k-1] * fmax[k][r]))));
				}
		}
	int ans = -INF;
	for (int i = 1; i <= n; i++) ans = max(ans, fmax[i][i+n-1]);
	cout << ans << endl;
	for (int i = 1; i <= n; i++)
		if (ans == fmax[i][i+n-1])
			cout << i << " ";
	return 0;
}
