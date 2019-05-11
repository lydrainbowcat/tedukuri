//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006, P = 20006, INF = 0x3f3f3f3f;
int n, p, k, d[N*N];
int Head[N*N], Edge[N*P], Next[N*P], Leng[N*P], tot = 0;
bool v[N*N];
queue<int> q;

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

void spfa() {
	memset(d, 0x3f, sizeof(d));
	d[1] = 0;
	v[1] = 1;
	q.push(1);
	while (q.size()) {
		int x = q.front();
		q.pop();
		v[x] = 0;
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i], z = Leng[i];
			if (d[y] > max(d[x], z)) {
				d[y] = max(d[x], z);
				if (!v[y]) {
					q.push(y);
					v[y] = 1;
				}
			}
		}
	}
}

int main() {
	cin >> n >> p >> k;
	for (int i = 1; i <= p; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		for (int j = 0; j <= k; j++) {
			add(x + j * n, y + j * n, z);
			add(y + j * n, x + j * n, z);
		}
		for (int j = 0; j < k; j++) {
			add(x + j * n, y + (j + 1) * n, 0);
			add(y + j * n, x + (j + 1) * n, 0);
		}
	}
	spfa();
	if (d[(k+1)*n] == INF) puts("-1");
	else cout << d[(k+1)*n] << endl;
	return 0;
}
