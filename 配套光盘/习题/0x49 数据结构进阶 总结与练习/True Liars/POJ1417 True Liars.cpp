//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006;
int n, p1, p2, fa[N], d[N], s[2][N], f[N][N], g[N][N];
int a1[N], a2[N], p[N], ans[N];

int get(int x) {
	if (x == fa[x]) return x;
	int root = get(fa[x]);
	d[x] ^= d[fa[x]];
	return fa[x] = root;
}

void work(int a, int b, int k) {
	int x = get(a), y = get(b);
	if (x == y) return;
	fa[y] = x;
	d[y] = k ^ d[a] ^ d[b];
	s[0][x] += s[d[y]][y];
	s[1][x] += s[d[y]^1][y];
}

void True_Liars() {
	memset(d, 0, sizeof(d));
	for (int i = 0; i < N; i++) {
		fa[i] = i;
		s[0][i] = 1;
		s[1][i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		int a, b;
		string str;
		cin >> a >> b >> str;
		work(a, b, str[0] != 'y');
	}
	memset(a1, 0, sizeof(a1));
	memset(a2, 0, sizeof(a2));
	int cnt = 0;
	for (int i = 1; i <= p1 + p2; i++)
		if (i == get(i)) {
			a1[++cnt] = s[0][i];
			a2[cnt] = s[1][i];
			p[cnt] = i;
		}
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	memset(g, 0, sizeof(g));
	for (int i = 1; i <= cnt; i++) {
		for (int t = p1; t >= a1[i]; t--)
			if (f[i-1][t-a1[i]]) {
				f[i][t] += f[i-1][t-a1[i]];
				g[i][t] = 0;
			}
		for (int t = p1; t >= a2[i]; t--)
			if (f[i-1][t-a2[i]]) {
				f[i][t] += f[i-1][t-a2[i]];
				g[i][t] = 1;
			}
	}
	if (f[cnt][p1] != 1) puts("no");
	else {
		int num = 0, now = p1 + p2;
		while (cnt > 0) {
			int w = g[cnt][p1], k = p[cnt];
			for (int i = 1; i <= now; i++)
				if (get(i) == k && d[i] == w)
					ans[num++] = i;
			p1 -= w ? a2[cnt] : a1[cnt];
			--cnt;
		}
		sort(ans, ans + num);
		for (int i = 0; i < num; i++) cout << ans[i] << endl;
		puts("end");
	}
}

int main() {
	while (cin >> n >> p1 >> p2 && n + p1 + p2) True_Liars();
	return 0;
}
