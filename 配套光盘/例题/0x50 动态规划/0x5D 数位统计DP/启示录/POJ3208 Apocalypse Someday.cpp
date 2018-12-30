//Author:XuHt
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
ll f[21][4];

void prework() {
	f[0][0] = 1;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 3; j++) {
			f[i+1][j+1] += f[i][j];
			f[i+1][0] += f[i][j] * 9;
		}
		f[i+1][3] += f[i][3] * 10;
	}
}

int main() {
	prework();
	int t;
	cin >> t;
	while (t--) {
		int n, m = 3;
		cin >> n;
		while (f[m][3] < n) ++m;
		for (int i = m, k = 0; i; i--) {
			for (int j = 0; j <= 9; j++) {
				ll cnt = f[i-1][3];
				if (j == 6 || k == 3)
					for (int l = max(3 - k - (j == 6), 0); l < 3; l++)
						cnt += f[i-1][l];
				if (cnt < n) n -= cnt;
				else {
					if (k < 3) {
						if (j == 6) ++k;
						else k = 0;
					}
					printf("%d", j);
					break;
				}
			}
		}
		puts("");
	}
	return 0;
}
