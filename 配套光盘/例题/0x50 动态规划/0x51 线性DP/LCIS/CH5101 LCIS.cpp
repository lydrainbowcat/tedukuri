//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 3006;
int n, a[N], b[N], f[N][N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++) {
		int val = 0;
		for (int j = 1; j <= n; j++) {
			f[i][j] = (a[i] == b[j] ? val + 1 : f[i-1][j]);
			if (b[j] < a[i]) val = max(val, f[i-1][j]);
		}
	}
	int ans = 0;
	for (int j = 1; j <= n; j++) ans = max(ans, f[n][j]);
	cout << ans << endl;
	return 0;
}
