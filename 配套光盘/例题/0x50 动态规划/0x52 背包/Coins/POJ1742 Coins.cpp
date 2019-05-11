//Author:XuHt
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 106, M = 100006;
int n, m, a[N], c[N], used[M];
bool f[M];

void Coins() {
	for (int i = 1; i <= m; i++) f[i] = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) used[j] = 0;
		for (int j = a[i]; j <= m; j++)
			if (!f[j] && f[j-a[i]] && used[j-a[i]] < c[i]) {
				f[j] = 1;
				used[j] = used[j-a[i]] + 1;
			}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) if (f[i]) ++ans;
	cout << ans << endl;
}

int main() {
	while (cin >> n >> m && n) Coins();
	return 0;
}
