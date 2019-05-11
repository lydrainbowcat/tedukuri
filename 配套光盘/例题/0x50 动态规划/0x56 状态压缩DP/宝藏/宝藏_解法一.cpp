#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 15, M = 1 << 12;
int n, m;
int a[N][N], f[N][M];
int expand[M], road[M][N];
vector<int> valid[M], cost[M];

void prework() {
	memset(road, 0x3f, sizeof(road));
	for (int k = 0; k < 1 << n; k++) {
		expand[k] = k;
		for (int x = 1; x <= n; x++)
			if (k >> (x - 1) & 1) {
				road[k][x] = 0;
				for (int y = 1; y <= n; y++) {
					if (a[x][y] == 0x3f3f3f3f) continue;
					expand[k] |= 1 << (y - 1);
					road[k][y] = min(road[k][y], a[x][y]);
				}
			}
	}
	for (int j = 0; j < 1 << n; j++) {
		// 这里由于n比较小就直接O(4^n)枚举了，实际上应该枚举j中的每个1选或不选，生成j的所有子集k，复杂度就是O(3^n)
		for (int k = 0; k < j; k++) {
			if ((j & k) == k && (j & expand[k]) == j) {
				valid[j].push_back(k);
				int sum = 0;
				for (int i = 1; i <= n; i++)
					if ((j ^ k) >> (i - 1) & 1) sum += road[k][i];
				cost[j].push_back(sum);
			}
		}
	}
}

int main() {
	cin >> n >> m;
	memset(a, 0x3f, sizeof(a));
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		a[x][y] = a[y][x] = min(a[x][y], z);
	}
	prework();
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; i++) f[1][1 << (i - 1)] = 0;
	int ans = f[1][(1 << n) - 1];
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < 1 << n; j++) {
			for (int p = 0; p < valid[j].size(); p++) {
				int k = valid[j][p];
				f[i][j] = min(f[i][j], f[i - 1][k] + (i - 1) * cost[j][p]);
			}
		}
		ans = min(ans, f[i][(1 << n) - 1]);
	}
	cout << ans << endl;
}
