//Author:xht37
#include <queue>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define pii pair<int, int>
#define x first
#define y second
#define mp make_pair
using namespace std;
const int N = 206, inf = 0x3f3f3f3f;
int n, m, ta, tb, t, d[N], now[N], pre[N], ans;
char s[N][N];
pii a[N], b[N];
int Head[N], Edge[N*N], Leng[N*N], Cost[N*N], Next[N*N], tot;
bitset<N> v;

inline int S(int i, int j) {
	return abs(a[i].x - b[j].x) + abs(a[i].y - b[j].y);
}

inline void add(int x, int y, int z, int w) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Cost[tot] = w;
	Next[tot] = Head[x];
	Head[x] = tot;
}

inline bool spfa() {
	v.reset();
	memset(d, 0x3f, sizeof(d));
	queue<int> q;
	q.push(0);
	v[0] = 1;
	d[0] = 0;
	now[0] = inf;
	while (q.size()) {
		int x = q.front();
		q.pop();
		v[x] = 0;
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i], z = Leng[i], w = Cost[i];
			if (!z || d[y] <= d[x] + w) continue;
			d[y] = d[x] + w;
			now[y] = min(now[x], z);
			pre[y] = i;
			if (!v[y]) {
				q.push(y);
				v[y] = 1;
			}
		}
	}
	return d[t<<1|1] != inf;
}

inline void upd() {
	ans += d[t<<1|1] * now[t<<1|1];
	int x = t << 1 | 1;
	while (x) {
		int i = pre[x];
		Leng[i] -= now[t];
		Leng[i^1] += now[t];
		x = Edge[i^1];
	}
}

inline void Going_Home() {
	ans = ta = tb = 0;
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] == 'H') a[++ta] = mp(i, j);
			else if (s[i][j] == 'm') b[++tb] = mp(i, j);
	t = ta;
	tot = 1;
	for (int i = 0; i <= (t << 1 | 1); i++) Head[i] = 0;
	for (int i = 1; i <= t; i++)
		for (int j = 1; j <= t; j++) {
			int k = S(i, j);
			add(i, j + t, 1, k);
			add(j + t, i, 0, -k);
		}
	for (int i = 1; i <= t; i++) {
		add(0, i, 1, 0);
		add(i, 0, 0, 0);
		add(i + t, t << 1 | 1, 1, 0);
		add(t << 1 | 1, i + t, 0, 0);
	}
	while (spfa()) upd();
	cout << ans << endl;
}

int main() {
	while (cin >> n >> m && n && m) Going_Home();
	return 0;
}
