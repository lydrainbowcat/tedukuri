//Author:xht37
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 206, M = 406, inf = 1e9;
int n, m, tot, ans, now[N], pre[N], v[N];
int Head[N], Edge[M], Leng[M], Next[M];

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

inline bool bfs() {
	memset(v, 0, sizeof(v));
	queue<int> q;
	q.push(1);
	v[1] = 1;
	now[1] = inf;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i], z = Leng[i];
			if (v[y] || !z) continue;
			now[y] = min(now[x], z);
			pre[y] = i;
			if (y == n) return 1;
			q.push(y);
			v[y] = 1;
		}
	}
	return 0;
}

inline void upd() {
	ans += now[n];
	int x = n;
	while (x != 1) {
		int i = pre[x];
		Leng[i] -= now[n];
		Leng[i^1] += now[n];
		x = Edge[i^1];
	}
}

void Drainage_Ditches() {
	memset(Head, 0, sizeof(Head));
	tot = 1;
	ans = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(x, y, z);
		add(y, x, 0);
	}
	while (bfs()) upd();
	cout << ans << endl;
}

int main() {
	while (cin >> m >> n) Drainage_Ditches();
	return 0;
}
