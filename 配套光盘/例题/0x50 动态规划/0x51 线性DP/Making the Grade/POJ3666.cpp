#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int SIZE = 2010;
int a[SIZE], c[SIZE], nums[SIZE];
int f[SIZE][SIZE];
int n;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		nums[i] = a[i];
	}
	sort(nums+1, nums+n+1);
	int m = unique(nums+1, nums+n+1)-nums-1;
	for (int i = 1; i <= n; i++)
		c[i] = lower_bound(nums+1, nums+m+1, a[i]) - nums;
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		int temp = f[i-1][0];
		for (int j = 1; j <= m; j++) {
			temp = min(temp, f[i-1][j]);
			f[i][j] = temp + abs(a[i] - nums[j]);
		}
	}
	int ans = 1 << 30;
	for (int i = 1; i <= m; i++)
		ans = min(ans, f[n][i]);
	cout << ans << endl;
}