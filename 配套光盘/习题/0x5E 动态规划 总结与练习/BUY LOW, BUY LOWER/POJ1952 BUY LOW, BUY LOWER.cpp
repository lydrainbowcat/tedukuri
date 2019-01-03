//Author:XuHt
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 5006, INF = 0x7fffffff;
int n, a[N], f[N], d[N][206];

void work(int x, int y) {
	d[x][0] = max(d[x][0], d[y][0]);
	for (int i = 1; i <= d[x][0]; i++) d[x][i] = d[x][i] + d[y][i];
	for (int i = 1; i <= d[x][0]; i++) {
		d[x][i+1] += d[x][i] / 10;
		d[x][i] %= 10;
	}
	if (d[x][d[x][0]+1] > 0) ++d[x][0];
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	d[0][0] = d[0][1] = 1;
	a[0] = INF;
	for (int i = 1; i <= n; i++) {
		for (int j = i - 1; j >= 0; j--)
			if (a[j] > a[i]) f[i] = max(f[i], f[j] + 1);
		for (int j = i - 1; j >= 0; j--) {
			if (a[j] > a[i] && f[i] == f[j] + 1) work(i, j);
			if (a[i] == a[j] && f[i] == f[j]) break;
		}
	}
	int z = 0;
	for (int i = 1; i <= n; i++) z = max(z, f[i]);
	for (int i = 1; i <= n; i++) if (f[i] == z) work(N - 1, i);
	cout << z << " ";
	for (int i = d[N-1][0]; i; i--) cout << d[N-1][i];
	cout << endl;
	return 0;
}
