//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006;
int n, d[N], trie[N*33][2], tot;
vector<pair<int, int> > e[N];
int Head[N], Edge[N*2], Leng[N*2], Next[N*2], num;
bool v[N];

void dfs(int x) {
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i], z = Leng[i];
		if (v[y]) continue;
		v[y] = 1;
		d[y] = d[x] ^ z;
		dfs(y);
	}
}

void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

void The_xor_longest_Path() {
	memset(d, 0, sizeof(d));
	memset(trie, 0, sizeof(trie));
	memset(v, 0, sizeof(v));
	memset(Head, 0, sizeof(Head));
	num = 0;
	v[0] = 1;
	tot = 1;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	dfs(0);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int p = 1;
		for (int j = 31; j >= 0; j--) {
			int k = (d[i] >> j) & 1;
			if (!trie[p][k]) trie[p][k] = ++tot;
			p = trie[p][k];
		}
		p = 1;
		if (i) {
			int w = 0;
			for (int j = 31; j >= 0; j--) {
				int k = (d[i] >> j) & 1;
				if (trie[p][k^1]) {
					w = (w << 1) + (k ^ 1);
					p = trie[p][k^1];
				} else {
					w = (w << 1) + k;
					p = trie[p][k];
				}
			}
			ans = max(ans, w ^ d[i]);
		}
	}
	cout << ans << endl;
}

int main() {
	while (cin >> n) The_xor_longest_Path();
	return 0;
}
