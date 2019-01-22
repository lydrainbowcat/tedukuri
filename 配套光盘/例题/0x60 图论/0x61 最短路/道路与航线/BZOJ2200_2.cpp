//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxT = 25006, maxRP = 150006, INF = 0x3f3f3f3f;
int T, R, P, S;
int Head[maxT], Edge[maxRP], Cost[maxRP], Next[maxRP], totS = 0;
int c[maxT], deg[maxT], d[maxT], totc = 0;
bool v[maxT];
queue<int> q;
priority_queue<pair<int, int> > Q;

inline void add(int A, int B, int C) {
	Edge[++totS] = B;
	Cost[totS] = C;
	Next[totS] = Head[A];
	Head[A] = totS;
}

void dfs(int i) {
	for (int j = Head[i]; j; j = Next[j])
		if (!c[Edge[j]]) {
			c[Edge[j]] = totc;
			dfs(Edge[j]);
		}
}

int main() {
	memset(d, 0x7f, sizeof(d));
	cin >> T >> R >> P >> S;
	for (int i = 1; i <= R; i++) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		add(A, B, C);
		add(B, A, C);
	}
	for (int i = 1; i <= T; i++)
		if (!c[i]) {
			c[i] = ++totc;
			dfs(i);
		}
	for (int i = 1; i <= P; i++) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		add(A, B, C);
		++deg[c[B]];
	}
	q.push(c[S]);
	for (int i = 1; i <= totc; i++) if (!deg[i]) q.push(i);
	d[S] = 0;
	while (q.size()) {
		int i = q.front();
		q.pop();
		for (int j = 1; j <= T; j++)
			if (c[j] == i) Q.push(make_pair(-d[j], j));
		while (Q.size()) {
			int x = Q.top().second;
			Q.pop();
			if (v[x]) continue;
			v[x] = 1;
			for (int j = Head[x]; j; j = Next[j]) {
				int y = Edge[j];
				if (d[x] + Cost[j] < d[y]) {
					d[y] = d[x] + Cost[j];
					if (c[x] == c[y]) Q.push(make_pair(-d[y], y));
				}
				if (c[x] != c[y] && !--deg[c[y]]) q.push(c[y]);
			}
		}
	}
	for (int i = 1; i <= T; i++)
		if (d[i] > INF) puts("NO PATH");
		else printf("%d\n", d[i]);
	return 0;
}
