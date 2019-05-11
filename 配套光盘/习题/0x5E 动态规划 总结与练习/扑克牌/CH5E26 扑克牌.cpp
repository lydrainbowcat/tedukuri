//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#define ull unsigned long long
using namespace std;
const int N = 20;
int n, num[N], c[N];
ull f[N][N][N][N];
char s[N];

ull dp(int a, int b, int c, int d) {
	if (f[a][b][c][d] != -1llu) return f[a][b][c][d];
	ull ans = 0;
	if (a > 0) ans += (ull)a * dp(a - 1, b, c, d);
	if (b > 0) ans += (ull)2 * b * (dp(a + 1, b - 1, c, d) - dp(a, b - 1, c, d));
	if (c > 0) ans += (ull)3 * c * (dp(a, b + 1, c - 1, d) - 2 * (dp(a + 1, b, c - 1, d) - dp(a, b, c - 1, d)));
	if (d > 0) ans += (ull)4 * d * (dp(a, b, c + 1, d - 1) - 3 * (dp(a, b + 1, c, d - 1) - 2 * (dp(a + 1, b, c, d - 1) - dp(a, b, c, d - 1))));
	return f[a][b][c][d] = ans;
}

int work(char c) {
	switch (c) {
		case 'T':
			return 10;
		case 'J':
			return 11;
		case 'Q':
			return 12;
		case 'K':
			return 13;
		case 'A':
			return 1;
	}
	return c - '0';
}

int main() {
	int T;
	cin >> T;
	memset(f, -1, sizeof(f));
	f[0][0][0][0] = 1;
	for (int t = 1; t <= T; t++) {
		memset(num, 0, sizeof(num));
		memset(c, 0, sizeof(c));
		cin >> n;
		for (int i = 1; i <= n; i++) {
			scanf("%s", s + 1);
			++num[work(s[1])];
		}
		for (int i = 1; i <= 13; i++) ++c[num[i]];
		printf("Case #%d: %llu\n", t, dp(c[1], c[2], c[3], c[4]));
	}
	return 0;
}
