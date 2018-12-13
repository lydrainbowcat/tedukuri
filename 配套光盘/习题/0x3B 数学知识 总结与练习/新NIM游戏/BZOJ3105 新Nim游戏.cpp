//Author:XuHt
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 106;
int k, a[N], b[N];
ll ans = 0;

int main() {
	cin >> k;
	for (int i = 1; i <= k; i++) {
		cin >> a[i];
		ans += a[i];
	}
	sort(a + 1, a + k + 1);
	for (int i = k; i; i--) {
		int x = a[i];
		for (int j = 30; j >= 0; j--)
			if ((a[i] >> j)) {
				if (!b[j]) {
					b[j] = a[i];
					break;
				} else a[i] ^= b[j];
			}
		if (a[i]) ans -= x;
	}
	cout << ans << endl;
	return 0;
}
