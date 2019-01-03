//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 206;
int n, a[N], tot, id = 0, c[N], cnt[N];
int o[N], nxt[N], x[N][N], f[N][N][N];

void Blocks() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	tot = 0;
	memset(cnt, 0, sizeof(cnt));
	int t = 1;
	while (t <= n) {
		c[++tot] = a[t];
		while (t <= n && a[t] == c[tot]) {
			++cnt[tot];
			++t;
		}
	}
	memset(o, 0, sizeof(o));
	for (int i = 1; i <= tot; i++) {
		nxt[i] = o[c[i]];
		o[c[i]] = i;
	}
	memset(x, 0, sizeof(x));
	for (int i = tot; i; i--)
		for (int j = 1; j <= n; j++)
			x[j][i] = x[j][i+1] + (j == c[i] ? cnt[i] : 0);
	memset(f, 0, sizeof(f));
	for (int len = 1; len <= tot; len++)
		for (int l = 1; l + len - 1 <= tot; l++) {
			int r = l + len - 1;
			for (int i = 0; i <= x[c[r]][r+1]; i++) {
				f[l][r][i] = f[l][r-1][0] + (cnt[r] + i) * (cnt[r] + i);
				for (int p = nxt[r]; p >= l; p = nxt[p])
					f[l][r][i] = max(f[l][r][i], f[l][p][cnt[r]+i] + f[p+1][r-1][0]);
			}
		}
	printf("Case %d: %d\n", ++id, f[1][tot][0]);
}

int main() {
	int t;
	cin >> t;
	while (t--) Blocks();
	return 0;
}
