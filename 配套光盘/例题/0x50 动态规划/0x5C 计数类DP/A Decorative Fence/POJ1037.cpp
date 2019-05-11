#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int t, n;
long long m, f[21][21][2];

void prework() {
	f[1][1][0] = f[1][1][1] = 1;
	for (int i = 2; i <= 20; i++)
		for (int j = 1; j <= i; j++) {
			for (int p = j; p <= i - 1; p++)
				f[i][j][0] += f[i - 1][p][1];
			for (int p = 1; p <= j - 1; p++)
				f[i][j][1] += f[i - 1][p][0];
		}
}

int main()
{
	prework();
	cin >> t;
	while (t--) {
		cin >> n >> m;
		bool used[21];
		memset(used, 0, sizeof(used));
		int last, k;
		// 第1块木板，既可能处于高位，也可能处于低位，单独处理
		for (int j = 1; j <= n; j++) {
			if (f[n][j][1] >= m) {
				last = j, k = 1;
				break;
			}
			else m -= f[n][j][1];
			if (f[n][j][0] >= m) {
				last = j, k = 0;
				break;
			}
			else m -= f[n][j][0];
		}
		used[last] = 1;
		printf("%d", last);
		// 第2~n块木板，高低位置、合法的长度范围与上一块木板有关
		for (int i = 2; i <= n; i++) {
			k ^= 1;
			// 真实长度为len，在剩余木板中排名为j
			int j = 0;
			for (int len = 1; len <= n; len++) {
				if (used[len]) continue;
				j++;
				if (k == 0 && len < last || k == 1 && len > last) {
					if (f[n - i + 1][j][k] >= m) {
						last = len;
						break;
					}
					else m -= f[n - i + 1][j][k];
				}
			}
			used[last] = 1;
			printf(" %d", last);
		}
		puts("");
	}
}
