#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int f[25][805]; // 前i个人，选了j个，辩方总分与控方总分的差为k=-400~400（平移到0~800）
int d[205][25][805]; // 记路径还是要三维，不然后面的更新可能会覆盖掉之前的记录
int n, m, a[205], b[205], suma, sumb, T;
vector<int> c;

void get_path(int i, int j, int k) {
	if (j == 0) return;
	int last = d[i][j][k];
	get_path(last - 1, j - 1, k - (a[last] - b[last]));
	c.push_back(last);
	suma += a[last], sumb += b[last];
}

int main() {
	while (cin >> n >> m && n) {
		for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
		memset(f, 0xcf, sizeof(f)); // -INF
		f[0][400] = 0; // f[0][0]第三维平移400
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= m; j++) // 不选i
				for (int k = 0; k <= 800; k++) d[i][j][k] = d[i - 1][j][k];
			for (int j = m; j; j--) // 选i
				for (int k = 0; k <= 800; k++) {
					if (k - (a[i] - b[i]) < 0 || k - (a[i] - b[i]) > 800) continue; // 超出范围
					if (f[j][k] < f[j - 1][k - (a[i] - b[i])] + a[i] + b[i]) {
						f[j][k] = f[j - 1][k - (a[i] - b[i])] + a[i] + b[i];
						d[i][j][k] = i;
					}
				}
		}
		int ans = 0;
		for (int k = 0; k <= 400; k++) {
			if (f[m][400 + k] >= 0 && f[m][400 + k] >= f[m][400 - k]) {
				ans = k + 400;
				break;
			}
			if (f[m][400 - k] >= 0) {
				ans = 400 - k;
				break;
			}
		}
		c.clear();
		suma = sumb = 0;
		get_path(n, m, ans);
		printf("Jury #%d\n", ++T);
		printf("Best jury has value %d for prosecution and value %d for defence:\n", suma, sumb);
		for (int i = 0; i < c.size(); i++) printf(" %d", c[i]);
		printf("\n\n");
	}
}