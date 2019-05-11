//Author:XuHt
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000006, INF = 0x3f3f3f3f;
int n, m, ans[N], maxy = -INF, c[N];
struct P {
	int t, x, y;
	bool operator < (const P a) const {
		return x < a.x || (x == a.x && y < a.y);
	}
} a[N], b[N];

void add(int y, int num) {
	while (y < maxy) {
		c[y] = max(c[y], num);
		y += y & -y;
	}
}

int ask(int y) {
	int ans = -INF;
	while (y) {
		ans = max(ans, c[y]);
		y -= y & -y;
	}
	return ans;
}

void re(int y) {
	while (y < maxy) {
		c[y] = -INF;
		y += y & -y;
	}
}

void work(int st, int ed, int w, int dx, int dy) {
	for (int i = st; i != ed; i += w) {
		int y = dy == 1 ? b[i].y : maxy - b[i].y;
		int num = dx * b[i].x + dy * b[i].y;
		if (a[b[i].t].t == 1) add(y, num);
		else ans[b[i].t] = min(ans[b[i].t], abs(num - ask(y)));
	}
	for (int i = st; i != ed; i += w)
		if (a[b[i].t].t == 1) re(dy == 1 ? b[i].y : maxy - b[i].y);
}

void CDQ(int l, int r) {
	int mid = (l + r) >> 1;
	if (l < mid) CDQ(l, mid);
	if (mid + 1 < r) CDQ(mid + 1, r);
	int tot = 0;
	for (int i = l; i <= r; i++)
		if ((i <= mid && a[i].t == 1) || (i > mid && a[i].t == 2)) {
			b[++tot] = a[i];
			b[tot].t = i;
		}
	sort(b + 1, b + tot + 1);
	work(1, tot + 1, 1, 1, 1);
	work(1, tot + 1, 1, 1, -1);
	work(tot, 0, -1, -1, -1);
	work(tot, 0, -1, -1, 1);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].x, &a[i].y);
		a[i].t = 1;
		maxy = max(maxy, a[i].y);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &a[i+n].t, &a[i+n].x, &a[i+n].y);
		maxy = max(maxy, a[i+n].y);
	}
	++maxy;
	memset(ans, 0x3f, sizeof(ans));
	memset(c, 0xcf, sizeof(c));
	CDQ(1, n + m);
	for (int i = 1; i <= n + m; i++)
		if (a[i].t == 2) printf("%d\n", ans[i]);
	return 0;
}
