//Author:XuHt
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 10006;
int p[20], n, t;
bool v[N], ans[N];

bool dfs(int x, int k) {
	if (v[x]) return 0;
	if (k == t) return 1;
	ans[k] = x & 1;
	v[x] = 1;
	if (dfs((x << 1) & (t - 1), k + 1)) return 1;
	if (dfs((x << 1 | 1) & (t - 1), k + 1)) return 1;
	v[x] = 0;
	return 0;
}

int main() {
	p[0] = 1;
	for (int i = 1; i < 20; i++) p[i] = p[i-1] << 1;
	cin >> n;
	cout << (t = p[n]) << ' ';
	dfs(0, 1);
	for (int i = 1; i < n; i++) putchar('0');
	for (int i = 1; i <= t - n + 1; i++) printf("%d", ans[i]);
	puts("");
	return 0;
}
