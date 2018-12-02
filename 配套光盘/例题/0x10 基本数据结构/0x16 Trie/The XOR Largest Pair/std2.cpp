//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006 * 33;
int trie[N][2];

int main() {
	int n;
	cin >> n;
	int ans = 0, t = 1;
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		int p = 1;
		for (int j = 31; j >= 0; j--) {
			int k = (a >> j) & 1;
			if (!trie[p][k]) trie[p][k] = ++t;
			p = trie[p][k];
		}
		p = 1;
		if (i > 1) {
			int w = 0;
			for (int j = 31; j >= 0; j--) {
				int k = (a >> j) & 1;
				if (trie[p][k^1]) {
					w = (w << 1) + (k ^ 1);
					p = trie[p][k^1];
				} else {
					w = (w << 1) + k;
					p = trie[p][k];
				}
			}
			ans = max(ans, w ^ a);
		}
	}
	cout << ans << endl;
	return 0;
}
