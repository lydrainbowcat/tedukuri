//Author:XuHt
#include <deque>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006, P = 20006;
int n, p, k, maxl = 0, d[N];
int Head[N], Edge[P], Next[P], Leng[P], tot = 0;
deque<int> q;
bool v[N];

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

int bfs(int now) {
	memset(d, 0x3f, sizeof(d));
	memset(v, 0, sizeof(v));
	d[1] = 0;
	q.push_back(1);
	while (q.size()) {
		int x = q.front();
		q.pop_front();
		if (v[x]) continue;
		v[x] = 1;
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i], z = Leng[i];
			if (v[y]) continue;
			if (z > now) {
				if (d[y] <= d[x] + 1) continue;
				d[y] = d[x] + 1;
				q.push_back(y);
			} else {
				if (d[y] <= d[x]) continue;
				d[y] = d[x];
				q.push_front(y);
			}
		}
	}
	return d[n];
}

int main() {
	cin >> n >> p >> k;
	for (int i = 1; i <= p; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
		maxl = max(maxl, z);
	}
	if (bfs(maxl) > k) {
		puts("-1");
		return 0;
	}
	int l = 0, r = maxl;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (bfs(mid) > k) l = mid + 1;
		else r = mid;
	}
	cout << l << endl;
	return 0;
}
