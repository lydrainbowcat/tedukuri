//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 16;
struct P {
	int x, y;
	bool z;
} ans[N];
int n, a[N][N];

bool pd() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++)
			if (a[i][j]) return 0;
	return 1;
}

void down() {
	int num[N][N];
	memset(num, -1, sizeof(num));
	for (int i = 0; i < 5; i++) {
		int k = 0;
		for (int j = 0; j < 7; j++)
			if (a[i][j]) num[i][k++] = j;
	}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++)
			a[i][j] = (num[i][j] == -1) ? 0 : a[i][num[i][j]];
}

bool work() {
	bool flag = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 7; j++)
			if (a[i][j]) {
				int t = i;
				while (t < 4 && a[t+1][j] == a[i][j]) ++t;
				if (t - i >= 2) {
					int x = i;
					while (x <= t) {
						int p = j, q = j;
						while (p < 6 && a[x][p+1] == a[i][j]) p++;
						while (q > 0 && a[x][q-1] == a[i][j]) q--;
						if (p - q >= 2)
							for (int y = q; y <= p; y++) a[x][y] = 0;
						++x;
					}
					for (x = i; x <= t; x++) a[x][j] = 0;
					flag = 1;
				}
			}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (a[i][j]) {
				int t = j;
				while (t < 6 && a[i][t+1] == a[i][j]) ++t;
				if (t - j >= 2) {
					int y = j;
					while (y <= t) {
						int p = i, q = i;
						while (p > 0 && a[p-1][y] == a[i][j]) p--;
						while (q < 6 && a[q+1][y] == a[i][j]) q++;
						if (q - p >= 2)
							for (int x = p; x <= q; x++) a[x][y] = 0;
						++y;
					}
					for (y = j; y <= t; y++) a[i][y] = 0;
					flag = 1;
				}
			}
	return flag;
}

void dfs(int now) {
	if (now > n) {
		if (pd()) {
			for (int i = 1; i <= n; i++)
				if (ans[i].z) printf("%d %d -1\n", ans[i].x + 1, ans[i].y);
				else printf("%d %d 1\n", ans[i].x, ans[i].y);
			exit(0);
		}
		return;
	}
	int num[N];
	memset(num, 0, sizeof(num));
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++) ++num[a[i][j]];
	for (int i = 1; i <= 10; i++)
		if (num[i] == 1 || num[i] == 2) return;
	int b[N][N];
	memcpy(b, a, sizeof(b));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 7; j++)
			if (a[i][j] != a[i+1][j]) {
				ans[now].x = i;
				ans[now].y = j;
				ans[now].z = (!a[i][j]);
				swap(a[i][j], a[i+1][j]);
				down();
				while (work()) down();
				dfs(now + 1);
				memcpy(a, b, sizeof(a));
			}
}

int main() {
	cin >> n;
	for (int i = 0; i < 5; i++)
		for (int j = 0; ; j++) {
			cin >> a[i][j];
			if (!a[i][j]) break;
		}
	dfs(1);
	puts("-1");
	return 0;
}
