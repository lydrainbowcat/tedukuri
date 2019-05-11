//Author:XuHt
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 106;
int n, m;
double a[N][N], b[N], ans;
vector<pair<int, int> > e[N];

void work() {
	for (int i = 1; i < n; i++) {
		int now = i;
		for (int j = i + 1; j < n; j++)
			if (fabs(a[j][i]) > fabs(a[now][i])) now = j;
		for (int j = 0; j <= n; j++) swap(a[i][j], a[now][j]);
		for (int j = i + 1; j <= n; j++) {
			double rate = a[j][i] / a[i][i];
			for (int k = 0; k <= n; k++) a[j][k] = a[i][k] * rate - a[j][k];
		}
	}
	for (int i = n; i; i--) {
		for (int j = i + 1; j <= n; j++) a[i][0] -= a[i][j] * b[j];
		b[i] = a[i][0] / a[i][i];
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		e[x].push_back(make_pair(y, z));
		if (x != y) e[y].push_back(make_pair(x, z));
	}
	for (int i = 0; i < 31; i++) {
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		for (int x = 1; x <= n; x++) a[x][x] = 1;
		for (int x = 1; x < n; x++) {
			int s = e[x].size();
			for (int j = 0; j < s; j++) {
				int y = e[x][j].first, z = e[x][j].second;
				double w = 1.0 / s;
				if ((z >> i) & 1) {
					a[x][y] += w;
					a[x][0] += w;
				} else a[x][y] -= w;
			}
		}
		work();
		ans += b[1] * (1 << i);
	}
	printf("%.3f\n", ans);
	return 0;
}
