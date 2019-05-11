//Author:XuHt
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 106, T = 20006, X = 10000;
int n, t, a[N], f[N][T], o[N];

int main() {
	cin >> n >> t;
	t += X;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	f[2][a[1]-a[2]+X] = -1;
	for (int i = 2; i < n; i++)
		for (int j = 0; j < (X << 1); j++)
			if (f[i][j]) {
				if (j + a[i+1] <= (X << 1)) f[i+1][j+a[i+1]] = 1;
				if (j - a[i+1] >= 0) f[i+1][j-a[i+1]] = -1;
			}
	for (int i = n; i > 1; i--)
		if ((o[i] = f[i][t]) == 1) t -= a[i];
		else t += a[i];
	int cnt = 0;
	for (int i = 2; i <= n; i++)
		if (o[i] == 1) printf("%d\n", i - cnt++ - 1);
	for (int i = 2; i <= n; i++)
		if (o[i] == -1) puts("1");
	return 0;
}
