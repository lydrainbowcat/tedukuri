//Author:XuHt
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106, INF = 0x3f3f3f3f;
char c[N];
int a[N], dp_max[N][N], dp_min[N][N];
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
	memset(dp_max, 0xcf, sizeof(dp_max));
	memset(dp_min, 0x3f, sizeof(dp_min));
	for (int i = 1; i <= (n << 1); i++) dp_max[i][i] = dp_min[i][i] = a[i];
	for (int len = 2; len <= n; len++)
		for (int l = 1; l + len - 1 <= (n << 1); l++) {
			int r = l + len - 1;
			for (int k = l + 1; k <= r; k++)
				if (c[k] == 't') {
					dp_max[l][r] = max(dp_max[l][r], dp_max[l][k-1] + dp_max[k][r]);
					dp_min[l][r] = min(dp_min[l][r], dp_min[l][k-1] + dp_min[k][r]);
				} else {
					dp_max[l][r] = max(dp_max[l][r], max(dp_max[l][k-1] * dp_max[k][r], dp_min[l][k-1] * dp_min[k][r]));
					dp_min[l][r] = min(dp_min[l][r], min(dp_max[l][k-1] * dp_max[k][r], min(dp_min[l][k-1] * dp_min[k][r], min(dp_max[l][k-1] * dp_min[k][r], dp_min[l][k-1] * dp_max[k][r]))));
				}
		}
	int ans = -INF;
	for (int i = 1; i <= n; i++) ans = max(ans, dp_max[i][i+n-1]);
	cout << ans << endl;
	for (int i = 1; i <= n; i++)
		if (ans == dp_max[i][i+n-1])
			cout << i << " ";
	return 0;
}
