//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006, INF = 0x3f3f3f3f;
int p[N];
bool v[N];

int main() {
	memset(v, 0, sizeof(v));
	v[1] = 1;
	int tot = 0;
	for (int i = 2; i <= 50000; i++) {
		if (!v[i]) p[++tot] = i;
		for (int j = 1, k; j <= tot; j++) {
			k = i * p[j];
			if (k > 50000) break;
			v[k] = 1;
			if (i % p[j] == 0) break;
		}
	}
	int n;
	cin >> n;
	while (n--) {
		int a0, a1, b0, b1;
		cin >> a0 >> a1 >> b0 >> b1;
		if (a1 > a0 || b1 < b0) {
			puts("0");
			continue;
		}
		int ans = 1;
		bool flag = 1;
		for (int i = 1; i <= tot; i++) {
			if (a0 == 1 && a1 == 1 && b0 == 1 && b1 == 1) break;
			int ta0 = 0, tb0 = 0, ta1 = 0, tb1 = 0;
			int la = 0, lb = 0, l = 0;
			int ra = INF, rb = INF, r = INF;
			while (a0 % p[i] == 0) {
				a0 /= p[i];
				ta0++;
			}
			while (b0 % p[i] == 0) {
				b0 /= p[i];
				tb0++;
			}
			while (a1 % p[i] == 0) {
				a1 /= p[i];
				ta1++;
			}
			while (b1 % p[i] == 0) {
				b1 /= p[i];
				tb1++;
			}
			if (ta0 < ta1 || tb0 > tb1) {
				flag = 0;
				break;
			}
			la = ta1;
			rb = tb1;
			if (ta0 > ta1) ra = ta1;
			if (tb0 < tb1) lb = tb1;
			l = max(la, lb);
			r = min(ra, rb);
			if (r < l) {
				flag = 0;
				break;
			}
			ans *= (r - l + 1);
		}
		if (!(a0 == 1 && a1 == 1 && b0 == 1 && b1 == 1)) {
			if (a1 > a0 || b1 < b0) flag = 0;
			if (a1 == a0 && a1 != 1) ans <<= 1;
			if (b1 == b0 && b1 != 1) ans <<= 1;
		}
		if (!flag) ans = 0;
		cout << ans << endl;
	}
	return 0;
}
