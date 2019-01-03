//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 306, INF = 0x3f3f3f3f;
int v, p, a[N], f[N][37], d[N][N];

void Post_Office() {
	for (int i = 1; i <= v; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= v; i++)
		for (int j = i + 1; j <= v; j++)
			d[i][j] = d[i][j-1] + a[j] - a[(i+j)>>1];
	for (int i = 1; i <= v; i++) {
		f[i][i] = 0;
		f[i][1] = d[1][i];
	}
	for (int j = 2; j <= p; j++)
		for (int i = j + 1; i <= v; i++) {
			f[i][j] = INF;
			for (int k = j - 1; k < i; k++)
				f[i][j] = min(f[i][j], f[k][j-1] + d[k+1][i]);
		}
	cout << f[v][p] << endl;
}

int main() {
	while (cin >> v >> p) Post_Office();
	return 0;
}
