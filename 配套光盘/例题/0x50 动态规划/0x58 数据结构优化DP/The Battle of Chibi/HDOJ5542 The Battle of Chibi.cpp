//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006, INF = 0x3f3f3f3f, P = 1000000007;
int n, m, a[N], b[N], c[N], f[N][N], num;

void add(int x, int y) {
	while (x <= n + 1) {
		c[x] = (c[x] + y) % P;
		x += x & -x;
	}
}

int ask(int x) {
	int ans = 0;
	while (x) {
		ans = (ans + c[x]) % P;
		x -= x & -x;
	}
	return ans;
}

void The_Battle_of_Chibi() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	memcpy(b, a, sizeof(b));
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b + 1;
	a[0] = f[0][0] = 1;
	for (int i = 1; i <= m; i++) {
		memset(c, 0, sizeof(c));
		add(1, f[i-1][0]);
		for (int j = 1; j <= n; j++) {
			f[i][j] = ask(a[j] - 1);
			add(a[j], f[i-1][j]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = (ans + f[m][i]) % P;
	printf("Case #%d: %d\n", ++num, ans);
}

int main() {
	int t;
	cin >> t;
	while (t--) The_Battle_of_Chibi();
	return 0;
}
