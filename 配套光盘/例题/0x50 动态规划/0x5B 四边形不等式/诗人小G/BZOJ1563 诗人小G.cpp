//Author:XuHt
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
#define ld long double
using namespace std;
const int N = 100006;
int n, l, p;
ll s[N];
ld f[N];
struct Q {
	int x, l, r;
} q[N];

int get(int i, int L, int R) {
	int ans;
	while (L <= R) {
		int mid = (L + R) >> 1;
		if (q[mid].l <= i && q[mid].r >= i) {
			ans = mid;
			break;
		}
		if (i >= q[mid].l) L = mid + 1;
		else R = mid - 1;
	}
	return q[ans].x;
}

ld calc(int i, int j) {
	ld ans = 1, num = abs((ld)(s[i] - s[j] + i - j - 1 - l));
	for (int i = 1; i <= p; i++) ans *= num;
	return ans + f[j];
}

void insert(int i, int &L, int &R) {
	int w = -1;
	while (L <= R)
		if (calc(q[R].l, i) <= calc(q[R].l, q[R].x)) w = q[R--].l;
		else {
			if (calc(q[R].r, q[R].x) > calc(q[R].r, i))  {
				int l = q[R].l, r = q[R].r;
				while (l < r) {
					int mid = (l + r) >> 1;
					if (calc(mid, i) > calc(mid, q[R].x)) l = mid + 1;
					else r = mid;
				}
				q[R].r = l - 1;
				w = l;
			}
			break;
		}
	if (w != -1) {
		q[++R].l = w;
		q[R].r = n;
		q[R].x = i;
	}
}

void G() {
	cin >> n >> l >> p;
	for (int i = 1; i <= n; i++) {
		char str[37];
		scanf("%s", str);
		s[i] = s[i-1] + strlen(str);
	}
	int L = 1, R = 1;
	q[1].x = 0;
	q[1].l = 1;
	q[1].r = n;
	for (int i = 1; i <= n; i++) {
		int j = get(i, L, R);
		f[i] = calc(i, j);
		while (L <= R && q[L].r <= i) ++L;
		q[L].l = i + 1;
		insert(i, L, R);
	}
	if (f[n] > 1e18) puts("Too hard to arrange");
	else cout << (ll)f[n] << endl;
	for (int i = 1; i <= 20; i++) putchar('-');
	puts("");
}

int main() {
	int t;
	cin >> t;
	while (t--) G();
	return 0;
}
