//Author:XuHt
#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 306;
map<string, int> mp;
int n, m, a[N][N], b[N];

int exgcd(int p, int q, int &x, int &y) {
	if (!q) {
		x = 1;
		y = 0;
		return p;
	}
	int d = exgcd(q, p % q, x, y);
	int z = x;
	x = y;
	y = z - y * (p / q);
	return d;
}

void Widget_Factory() {
	memset(a, 0, sizeof(a));
	for (int i = 1; i <= m; i++) {
		int k;
		char s1[6], s2[6];
		scanf("%d %s %s", &k, s1, s2);
		b[i] = (mp[s2] - mp[s1] + 1) % 7;
		while (k--) {
			int x;
			scanf("%d", &x);
			(++a[i][x]) %= 7;
		}
	}
	int w = 0;
	for (int i = 1; i <= n; i++) {
		int t = 0;
		for (int j = w + 1; j <= m; j++)
			if (a[j][i] && (!t || a[j][i] > a[t][i])) t = j;
		if (!t) continue;
		swap(b[++w], b[t]);
		for (int j = 1; j <= n; j++) swap(a[w][j], a[t][j]);
		for (int j = 1; j <= m; j++) {
			if (w == j || !a[j][i]) continue;
			int z = a[j][i];
			for (int k = 1; k <= n; k++)
				a[j][k] = (a[j][k] * a[w][i] - a[w][k] * z) % 7;
			b[j] = (b[j] * a[w][i] - b[w] * z) % 7;
		}
	}
	for (int i = w + 1; i <= m; i++)
		if (b[i] %= 7) {
			puts("Inconsistent data.");
			return;
		}
	if (w < n) {
		puts("Multiple solutions.");
		return;
	}
	for (int i = 1; i <= n; i++) {
		int x, y;
		int d = exgcd(a[i][i], 7, x, y);
		if (b[i] % d) {
			puts("Inconsistent data.");
			return;
		}
		else if (i < n) printf("%d ", ((x * b[i] / d - 3) % 7 + 7) % 7 + 3);
		else printf("%d\n", ((x * b[i] / d - 3) % 7 + 7) % 7 + 3);
	}
}

int main() {
	mp["MON"] = 1;
	mp["TUE"] = 2;
	mp["WED"] = 3;
	mp["THU"] = 4;
	mp["FRI"] = 5;
	mp["SAT"] = 6;
	mp["SUN"] = 7;
	while (cin >> n >> m && n && m) Widget_Factory();
	return 0;
}
