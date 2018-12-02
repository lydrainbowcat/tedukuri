//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006;
struct A {
	int a, w, prv, nxt;
	bool operator < (const A x) const {
		return a < x.a;
	}
} a[N];
int n, b[N];
struct ANS {
	int x, k;
} ans[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].a);
		a[i].w = i;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		b[a[i].w] = i;
		a[i].prv = i - 1;
		a[i].nxt = i + 1;
	}
	int l = 1, r = n;
	for (int i = n; i > 1; i--) {
		if (b[i] == r) {
			ans[i].x = a[r].a - a[a[r].prv].a;
			ans[i].k = a[a[r].prv].w;
			r = a[r].prv;
		} else if (b[i] == l) {
			ans[i].x = a[a[l].nxt].a - a[l].a;
			ans[i].k = a[a[l].nxt].w;
			l = a[l].nxt;
		} else {
			ans[i].x = a[a[b[i]].nxt].a - a[b[i]].a;
			ans[i].k = a[a[b[i]].nxt].w;
			if (a[b[i]].a - a[a[b[i]].prv].a <= ans[i].x) {
				ans[i].x = a[b[i]].a - a[a[b[i]].prv].a;
				ans[i].k = a[a[b[i]].prv].w;
			}
		}
		a[a[b[i]].prv].nxt = a[b[i]].nxt;
		a[a[b[i]].nxt].prv = a[b[i]].prv;
	}
	for (int i = 2; i <= n; i++) printf("%d %d\n", ans[i].x, ans[i].k);
	return 0;
}
