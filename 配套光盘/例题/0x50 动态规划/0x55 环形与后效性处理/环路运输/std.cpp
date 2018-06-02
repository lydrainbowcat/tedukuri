#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[2000010], q[2000010], n, ans;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		a[n + i] = a[i];
	}
	int l = 1, r = 1;
	q[1] = 1;
	for (int i = 2; i <= 2 * n; i++) {
		while (l <= r && q[l] < i - n / 2) l++;
		ans = max(ans, a[i] + a[q[l]] + i - q[l]);
		while (l < r && a[i] - i >= a[q[r]] - q[r]) r--;
		q[++r] = i;
	}
	cout << ans << endl;
}
