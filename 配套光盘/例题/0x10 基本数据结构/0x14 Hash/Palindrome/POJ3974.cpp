#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
typedef unsigned long long ull;
const int MAXN = 1000007;
char s[MAXN];
ull f1[MAXN], f2[MAXN], p[MAXN];

inline ull H(int i, int j) {
	return (f1[j] - f1[i - 1] * p[j - i + 1]);
}

inline ull H2(int i, int j) {
	return (f2[i] - f2[j + 1] * p[j - i + 1]);
}

int main() {
	int ans = 0, cases = 0;
	p[0] = 1;
	for (int i = 1; i < MAXN; ++i) p[i] = p[i - 1] * 131;
	while (1) {
		++cases;
		ans = 0;
		scanf("%s", s + 1);
		int L = strlen(s + 1);
		if (L == 3 && s[1] == 'E' && s[2] == 'N' && s[3] == 'D') break;
		f2[L + 1] = 0;
		for (int i = 1; i <= L; ++i) f1[i] = f1[i - 1] * 131 + s[i] - 'a' + 1;
		for (int i = L; i >= 1; --i) f2[i] = f2[i + 1] * 131 + s[i] - 'a' + 1; 
		for (int pos = 1; pos <= L; ++pos) {
			int l = 1, r = min(pos - 1, L - pos), mid;
			while (l < r) {
				mid = (l + r + 1) >> 1;
				if (H(pos - mid, pos - 1) == H2(pos + 1, pos + mid)) {
					l = mid;
				} else {
					r = mid - 1;
				}
			}
			ans = max(l * 2 + 1, ans);
			l = 1, r = min(pos - 1, L - pos + 1);
			while (l < r) {
				mid = (l + r + 1) >> 1;
				if (H(pos - mid, pos - 1) == H2(pos, pos + mid - 1)) {
					l = mid;
				} else {
					r = mid - 1;
				}
			}
			ans = max(l * 2, ans);
		}
		printf("Case %d: %d\n", cases, ans);
	}
	return 0;
}
