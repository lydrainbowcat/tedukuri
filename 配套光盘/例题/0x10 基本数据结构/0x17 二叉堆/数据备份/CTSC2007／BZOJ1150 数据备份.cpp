//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006;
struct L {
	int d, prv, nxt, th;
} p[N];
struct H {
	int D, tp;
} h[N];
int tot = 0;

void up(int i) {
	while (i > 1) {
		if (h[i].D < h[i>>1].D) {
			swap(h[i], h[i>>1]);
			swap(p[h[i].tp].th, p[h[i>>1].tp].th);
			i >>= 1;
		} else return;
	}
}

void down(int i) {
	int ii = i << 1;
	while (ii <= tot) {
		if (ii < tot && h[ii].D > h[ii+1].D) ++ii;
		if (h[ii].D < h[i].D) {
			swap(h[ii], h[i]);
			swap(p[h[ii].tp].th, p[h[i].tp].th);
			i = ii;
			ii = i << 1;
		} else return;
	}
}

void DeL(int i) {
	p[p[i].prv].nxt = p[i].nxt;
	p[p[i].nxt].prv = p[i].prv;
}

void DeH(int i) {
	if (i == --tot + 1) return;
	swap(h[i], h[tot+1]);
	swap(p[h[i].tp].th, p[h[tot+1].tp].th);
	up(i);
	down(i);
}

int main() {
	int n, k, pre;
	cin >> n >> k >> pre;
	for (int i = 1; i < n; i++) {
		int w;
		scanf("%d", &w);
		p[i].d = w - pre;
		p[i].prv = i - 1;
		p[i].nxt = i + 1;
		p[i].th = ++tot;
		pre = w;
		h[tot].D = p[i].d;
		h[tot].tp = i;
		up(tot);
	}
	int ans = 0;
	for (int i = 1; i <= k; i++) {
		ans += h[1].D;
		if (!p[h[1].tp].prv || p[h[1].tp].nxt == n) {
			if (!p[h[1].tp].prv) {
				DeH(p[p[h[1].tp].nxt].th);
				DeL(p[h[1].tp].nxt);
			} else {
				DeH(p[p[h[1].tp].prv].th);
				DeL(p[h[1].tp].prv);
			}
			DeL(h[1].tp);
			DeH(1);
		} else {
			int tp0 = h[1].tp;
			h[1].D = p[p[h[1].tp].prv].d + p[p[h[1].tp].nxt].d - p[h[1].tp].d;
			p[h[1].tp].d = h[1].D;
			down(1);
			DeH(p[p[tp0].prv].th);
			DeH(p[p[tp0].nxt].th);
			DeL(p[tp0].prv);
			DeL(p[tp0].nxt);
		}
	}
	cout << ans << endl;
	return 0;
}
