//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 60, S = 600;
int n;
struct A {
	int a[S], len;
	inline A operator / (const int x) const {
		A ans;
		memset(ans.a, 0, sizeof(ans.a));
		ans.len = 0;
		int num = 0;
		for (int i = len; i; i--) {
			num = num * 10 + a[i];
			ans.a[i] = num / x;
			num %= x;
			if (!ans.len && ans.a[i]) ans.len = i;
		}
		return ans;
	}
	inline A operator + (const A x) const {
		A ans;
		memset(ans.a, 0, sizeof(ans.a));
		for (int i = 1; i <= max(len, x.len); i++) {
			ans.a[i] += a[i] + x.a[i];
			ans.a[i+1] = ans.a[i] / 10;
			ans.a[i] %= 10;
		}
		ans.len = max(len, x.len);
		if (ans.a[ans.len+1]) ++ans.len;
		return ans;
	}
	inline A operator * (const A x) const {
		A ans;
		memset(ans.a, 0, sizeof(ans.a));
		for (int i = 1; i <= len; i++)
			for (int j = 1; j <= x.len; j++) {
				ans.a[i+j-1] += a[i] * x.a[j];
				ans.a[i+j] += ans.a[i+j-1] / 10;
				ans.a[i+j-1] %= 10;
			}
		ans.len = len + x.len - 1;
		if (ans.a[ans.len+1]) ++ans.len;
		return ans;
	}
} f[N], p[N];

inline A C(int x, int y) {
	A ans;
	ans.len = ans.a[1] = 1;
	for (int i = y, j = 1; j <= x; i--, j++) {
		int t = i;
		A tmp;
		tmp.len = 0;
		while (t) {
			tmp.a[++tmp.len] = t % 10;
			t /= 10;
		}
		ans = ans * tmp / j;
	}
	return ans;
}

inline void print(A x) {
	for (int i = x.len; i; i--) printf("%d", x.a[i]);
	puts("");
}

int main() {
	for (int i = 1; i <= 50; i++) {
		ll t = (1ll << i) - 1;
		while (t) {
			p[i].a[++p[i].len] = t % 10;
			t /= 10;
		}
	}
	f[1].len = f[2].len = f[1].a[1] = f[2].a[1] = 1;
	for (int i = 3; i <= 50; i++)
		for (int j = 1; j <= i - 1; j++)
			f[i] = f[i] + C(j - 1, i - 2) * f[j] * f[i-j] * p[j];
	while (cin >> n && n) print(f[n]);
	return 0;
}
