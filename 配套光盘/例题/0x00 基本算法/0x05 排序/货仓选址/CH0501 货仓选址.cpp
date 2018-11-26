//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 100006;
int n, a[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	ll ans = 0;
	for (int i = 1; i <= n / 2; i++)
		ans += a[n-i+1] - a[i];
	cout << ans << endl;
	return 0;
}
