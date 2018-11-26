//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10006;
int n, x[N], y[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d %d", &x[i], &y[i]);
	sort(x + 1, x + n + 1);
	sort(y + 1, y + n + 1);
	for (int i = 1; i <= n; i++) x[i] -= i;
	sort(x + 1, x + n + 1);
	int ans = 0;
	for (int i = 1; i <= n / 2; i++)
		ans += x[n+1-i] - x[i] + y[n+1-i] - y[i];
	cout << ans << endl;
	return 0;
}
