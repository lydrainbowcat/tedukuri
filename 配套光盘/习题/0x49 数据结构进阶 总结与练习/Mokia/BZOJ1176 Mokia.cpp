//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006, A = 10006, W = 2000006;
int w, o, tot = 0, cnt = 0, ans[A] ,c[W];
struct P {
	int x, y, z, o, id;
	bool operator < (const P p) const {
		return x < p.x || (x == p.x && (y < p.y || (y == p.y && o < p.o)));
	}
} a[N], b[N];

inline void add(int x, int y) {
	while (x <= w) {
		c[x] += y;
		x += x & -x;
	}
}

inline int ask(int x) {
	int ans = 0;
	while (x) {
		ans += c[x];
		x -= x & -x;
	}
	return ans;
}

inline void CDQ(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1, t1 = l, t2 = mid + 1;
	for (int i = l; i <= r; i++)
		if (a[i].id <= mid && !a[i].o) add(a[i].y, a[i].z);
		else if (a[i].id > mid && a[i].o) ans[a[i].o] += ask(a[i].y) * a[i].z;
	for (int i = l; i <= r; i++)
		if (a[i].id <= mid && !a[i].o) add(a[i].y, -a[i].z);
	for (int i = l; i <= r; i++)
		if (a[i].id <= mid) b[t1++] = a[i];
		else b[t2++] = a[i];
	for (int i = l; i <= r; i++) a[i] = b[i];
	CDQ(l, mid);
	CDQ(mid + 1, r);
}

inline void add(int x, int y, int z, int o, int id) {
	a[tot].x = x;
	a[tot].y = y;
	a[tot].z = z;
	a[tot].o = o;
	a[tot].id = id;
}

int main() {
	cin >> w >> w;
	memset(ans, 0, sizeof(ans));
	while (scanf("%d", &o) && o != 3)
		if (o == 1) {
			a[++tot].o = 0;
			a[tot].id = tot;
			scanf("%d %d %d", &a[tot].x, &a[tot].y, &a[tot].z);
		} else {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			add(--x1, --y1, 1, ++cnt, ++tot);
			add(x1, y2, -1, cnt, ++tot);
			add(x2, y1, -1, cnt, ++tot);
			add(x2, y2, 1, cnt, ++tot);
		}
	sort(a + 1, a + tot + 1);
	CDQ(1, tot);
	for (int i = 1; i <= cnt; i++) printf("%d\n", ans[i]);
	return 0;
}
