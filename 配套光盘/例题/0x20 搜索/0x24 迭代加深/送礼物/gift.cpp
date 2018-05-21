#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, half, m, g[50];
unsigned int w, ans, a[(1 << 24) + 1];

void dfs1(int i, unsigned int sum) {
	if (i == half) {
		a[++m] = sum;
		return;
	}
	dfs1(i + 1, sum);
	if (sum + g[i] <= w) dfs1(i + 1, sum + g[i]);
}

void calc(unsigned int val) {
	int rest = w - val;
	int l = 1, r = m;
	while (l < r) {
		int mid = (l + r + 1) / 2;
		if (a[mid] <= rest) l = mid; else r = mid - 1;
	}
	ans = max(ans, a[l] + val);
}

void dfs2(int i, unsigned int sum) {
	if (i == n + 1) {
		calc(sum);
		return;
	}
	dfs2(i + 1, sum);
	if (sum + g[i] <= w) dfs2(i + 1, sum + g[i]);
}

int main() {
	cin >> w >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &g[i]);
	sort(g + 1, g + n + 1);
	reverse(g + 1, g + n + 1);
	half = n / 2 + 3;
	dfs1(1, 0);
	sort(a + 1, a + m + 1);
	m = unique(a + 1, a + m + 1) - (a + 1);
	dfs2(half, 0);
	cout << ans << endl;
}