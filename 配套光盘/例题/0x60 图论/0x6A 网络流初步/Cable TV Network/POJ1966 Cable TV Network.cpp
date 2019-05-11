//Author:xht37
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 56, M = 20006, INF = 0x3f3f3f3f;
int n, m, s, t;
int a[N*N], b[N*N], d[N<<1];
int Head[N<<1], Edge[M], Leng[M], Next[M], tot;

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
	Edge[++tot] = x;
	Leng[tot] = 0;
	Next[tot] = Head[y];
	Head[y] = tot;
}

inline bool bfs() {
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(s);
	d[s] = 1;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i], z = Leng[i];
			if (z && !d[y]) {
				q.push(y);
				d[y] = d[x] + 1;
				if (y == t) return 1;
			}
		}
	}
	return 0;
}

inline int dinic(int x, int f) {
	if (x == t) return f;
	int rest = f;
	for (int i = Head[x]; i && rest; i = Next[i]) {
		int y = Edge[i], z = Leng[i];
		if (z && d[y] == d[x] + 1) {
			int k = dinic(y, min(rest, z));
			if (!k) d[y] = 0;
			Leng[i] -= k;
			Leng[i^1] += k;
			rest -= k;
		}
	}
	return f - rest;
}

inline void Cable_TV_Network() {
	for (int i = 0; i < m; i++) {
		char str[20];
		scanf("%s", str);
		a[i] = b[i] = 0;
		int j;
		for (j = 1; str[j] != ','; j++) a[i] = a[i] * 10 + str[j] - '0';
		for (j++; str[j] != ')'; j++) b[i] = b[i] * 10 + str[j] - '0';
	}
	int ans = INF;
	for (s = 0; s < n; s++)
		for (t = 0; t < n; t++)
			if (s != t) {
				memset(Head, 0, sizeof(Head));
				tot = 1;
				int maxf = 0;
				for (int i = 0; i < n; i++)
					if (i == s || i == t) add(i, i + n, INF);
					else add(i, i + n, 1);
				for (int i = 0; i < m; i++) {
					add(a[i] + n, b[i], INF);
					add(b[i] + n, a[i], INF);
				}
				while (bfs()) {
					int num;
					while ((num = dinic(s, INF))) maxf += num;
				}
				ans = min(ans, maxf);
			}
	if (n <= 1 || ans == INF) ans = n;
	cout << ans << endl;
}

int main() {
	while (cin >> n >> m) Cable_TV_Network();
	return 0;
}
