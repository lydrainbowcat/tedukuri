//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106, M = 12, X = 60000;
int n, m, f[N][X];
int p[] = {0,1,3,9,27,81,243,729,2187,6561,19683,59049,177147};
char s[N][M];

void dp(int x, int y, int now, int nxt, int cnt) {
	if (y > m) {
		if (x < n) {
			dp(x + 1, 1, nxt, 0, 0);
			f[x][now] = max(f[x][now], f[x+1][nxt] + cnt);
			return;
		}
		f[x][now] = max(f[x][now], cnt);
		return;
	}
	if (y == 1) {
		if (f[x][now] != -1) return;
		f[x][now] = 0;
	}
	int k = now / p[y] % 3;
	if (k == 2) dp(x, y + 1, now, nxt + p[y], cnt);
	else if (k || s[x][y] == 'H') dp(x, y + 1, now, nxt, cnt);
	else {
		dp(x, y + 1, now, nxt, cnt);
		int num = p[y] << 1, w = now / p[y+1] % 3;;
		if (w == 2) num += p[y+1];
		w = now / p[y+2] % 3;
		if (w == 2) num += p[y+2];
		dp(x, y + 3, now, nxt + num, cnt + 1);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	memset(f, -1, sizeof(f));
	dp(1, 1, 0, 0, 0);
	cout << f[1][0] << endl;
	return 0;
}
