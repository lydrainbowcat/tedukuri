//Author:XuHt
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
unsigned int g[50], w, ans;
vector<unsigned int> a;

void dfs1(int k, unsigned int x) {
	if (!k) {
		a.push_back(x);
		return;
	}
	dfs1(k - 1, x);
	if (x + g[k] <= w) dfs1(k - 1, x + g[k]);
}

void dfs2(int i, unsigned int x) {
	if (i == n + 1) {
		int y = *--upper_bound(a.begin(), a.end(), w - x);
		ans = max(ans, x + y);
		return;
	}
	dfs2(i + 1, x);
	if (x + g[i] <= w) dfs2(i + 1, x + g[i]);
}

bool cmp(unsigned int x, unsigned int y) {
	return x > y;
}

int main() {
	cin >> w >> n;
	for (int i = 1; i <= n; i++) cin >> g[i];
	sort(g + 1, g + n + 1, cmp);
	int k = n / 2 + 3;
	dfs1(k - 1, 0);
	sort(a.begin(), a.end());
	m = unique(a.begin(), a.end()) - a.begin();
	dfs2(k, 0);
	cout << ans << endl;
	return 0;
}
