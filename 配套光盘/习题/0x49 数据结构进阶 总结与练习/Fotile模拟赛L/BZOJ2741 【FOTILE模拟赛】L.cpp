//Author:XuHt
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 12006;
int n, m, a[N], ed[N], trie[N*32][2], pos[N*32], f[86][N], tot = 0;

void add(int pre, int now, int num) {
	int p = ed[num] = ++tot;
	pos[p] = num;
	for (int i = 30; i >= 0; i--) {
		int j = (now >> i) & 1;
		trie[p][j^1] = trie[pre][j^1];
		p = trie[p][j] = ++tot;
		pos[p] = num;
		pre = trie[pre][j];
	}
}

int ask(int len, int r, int x) {
	int ans = 0, p = ed[r];
	for (int i = 30; i >= 0; i--) {
		int j = ((x >> i) & 1) ^ 1;
		if (pos[trie[p][j]] >= len) ans |= 1 << i;
		else j ^= 1;
		p = trie[p][j];
	}
	return ans;
}

int main() {
	memset(pos, -1, sizeof(pos));
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		a[i] ^= a[i-1];
	}
	int t = sqrt(m), len = n / t;
	if (n % t) ++len;
	add(0, 0, 0);
	for (int i = 1; i <= n; i++) add(ed[i-1], a[i], i);
	for (int i = 0; i < t; i++)
		for (int j = i * len + 1; j <= n; j++)
			f[i][j] = max(f[i][j-1], ask(i * len, j - 1, a[j]));
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		x = (x + ans) % n + 1;
		y = (y + ans) % n + 1;
		if (x > y) swap(x, y);
		int p = --x / len;
		if (x % len) ++p;
		ans = p * len < y ? f[p][y] : 0;
		p = min(p * len, y);
		for (int j = x; j <= p; j++)
			ans = max(ans, ask(x, y, a[j]));
		printf("%d\n", ans);
		ans %= n;
	}
	return 0;
}
