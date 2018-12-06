//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 20;
int n, a[N], dep;

int gj() {
	int cnt = 0;
	for (int i = 1; i < n; i++)
		if (a[i] + 1 != a[i+1]) cnt++;
	if (a[n] != n) return cnt + 1;
	return cnt;
}

void work(int l, int r, int t) {
	int b[N], p = r;
	for (int i = l; i <= t; i++) {
		b[i] = a[++p];
		if (p == t) p = l - 1;
	}
	for (int i = l; i <= t; i++) a[i] = b[i];
}

bool dfs(int now) {
	int cnt = gj();
	if (!cnt) return 1;
	if (3 * now + cnt > 3 * dep) return 0;
	int c[N];
	memcpy(c, a, sizeof(c));
	for (int l = 1; l <= n; l++)
		for (int r = l; r <= n; r++)
			for (int t = r + 1; t <= n; t++) {
				work(l, r, t);
				if (dfs(now + 1)) return 1;
				memcpy(a, c, sizeof(a));
			}
	return 0;
}

void Booksort() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (dep = 0; dep <= 4; dep++)
		if (dfs(0)) {
			cout << dep << endl;
			return;
		}
	puts("5 or more");
}

int main() {
	int t;
	cin >> t;
	while (t--) Booksort();
	return 0;
}
