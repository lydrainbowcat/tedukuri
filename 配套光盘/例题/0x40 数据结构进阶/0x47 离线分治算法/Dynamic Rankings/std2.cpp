//Author:XuHt
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 100006, INF = 0x3f3f3f3f;
struct P {
	int p, x, y, z;
} q[3*N], lq[3*N], rq[3*N];
int n, m, t = 0, p = 0, a[N], c[N], ans[N];

int ask(int x) {
	int ans = 0;
	while (x) {
		ans += c[x];
		x -= x & -x;
	}
	return ans;
}

void add(int x, int y) {
	while (x <= n) {
		c[x] += y;
		x += x & -x;
	}
}

void work(int lval, int rval, int st, int ed) {
	if (st > ed) return;
	if (lval == rval) {
		for (int i = st; i <= ed; i++)
			if (q[i].p > 0) ans[q[i].p] = lval;
		return;
	}
	int mid = (lval + rval) >> 1, lt = 0, rt = 0;
	for (int i = st; i <= ed; i++)
		if (q[i].p <= 0) {
			if (q[i].y <= mid) {
				add(q[i].x, q[i].z);
				lq[++lt] = q[i];
			}
			else rq[++rt] = q[i];
		} else {
			int cnt = ask(q[i].y) - ask(q[i].x - 1);
			if (cnt >= q[i].z) lq[++lt] = q[i];
			else {
				q[i].z -= cnt;
				rq[++rt] = q[i];
			}
		}
	for (int i = ed; i >= st; i--)
		if (q[i].p <= 0 && q[i].y <= mid) add(q[i].x, -q[i].z);
	for (int i = 1; i <= lt; i++) q[st+i-1] = lq[i];
	for (int i = 1; i <= rt; i++) q[st+lt+i-1] = rq[i];
	work(lval, mid, st, st + lt - 1);
	work(mid + 1, rval, st + lt, ed);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		q[++t].p = 0;
		q[t].x = i;
		q[t].y = a[i];
		q[t].z = 1;
	}
	for (int i = 1; i <= m; i++) {
		char s[2];
		scanf("%s", s);
		if (s[0] == 'Q') {
			q[++t].p = ++p;
			scanf("%d %d %d", &q[t].x, &q[t].y, &q[t].z);
		} else {
			int x, y;
			scanf("%d %d", &x, &y);
			q[++t].p = -1;
			q[t].x = x;
			q[t].y = a[x];
			q[t].z = -1;
			q[++t].p = 0;
			q[t].x = x;
			q[t].y = y;
			q[t].z = 1;
			a[x] = y;
		}
	}
	work(0, INF, 1, t);
	for (int i = 1; i <= p; i++) printf("%d\n", ans[i]);
	return 0;
}
