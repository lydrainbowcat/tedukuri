//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006;
int n, m, a[N], x[N], y[N], cinema[N*3], tot = 0, k, ans[N*3];

int find(int f) {
	return lower_bound(cinema + 1, cinema + k + 1, f) - cinema;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		cinema[++tot] = a[i];
	}
	cin >> m;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &x[i]);
		cinema[++tot] = x[i];
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &y[i]);
		cinema[++tot] = y[i];
	}
	sort(cinema + 1, cinema + tot + 1);
	k = unique(cinema + 1, cinema + tot + 1) - (cinema + 1);
	memset(ans, 0, sizeof(ans));
	for (int i = 1; i <= n; i++) ans[find(a[i])]++;
	int ans0 = 1, ans1 = 0, ans2 = 0;
	for (int i = 1; i <= m; i++) {
		int ansx = ans[find(x[i])], ansy = ans[find(y[i])];
		if (ansx > ans1 || (ansx == ans1 && ansy > ans2)) {
			ans0 = i;
			ans1 = ansx;
			ans2 = ansy;
		}
	}
	cout << ans0 << endl;
	return 0;
}
