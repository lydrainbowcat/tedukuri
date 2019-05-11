#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
int n, m;
pair<string, int> a[100005];

int calc(int bit, int now) {
	for (int i = 1; i <= n; i++) {
		int x = a[i].second >> bit & 1;
		if (a[i].first == "AND") now &= x;
		else if (a[i].first == "OR") now |= x;
		else now ^= x;
	}
	return now;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		char str[5];
		int x;
		scanf("%s%d", str, &x);
		a[i] = make_pair(str, x);
	}
	int val = 0, ans = 0;
	for (int bit = 29; bit >= 0; bit--) {
		int res0 = calc(bit, 0);
		int res1 = calc(bit, 1);
		if (val + (1 << bit) <= m && res0 < res1)
			val += 1 << bit, ans += res1 << bit;
		else
			ans += res0 << bit;
	}
	cout << ans << endl;
}
