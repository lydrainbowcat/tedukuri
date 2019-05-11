//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 500006, M = 5000006;
int n, m, d[N];
int Head[N], Edge[M], Leng[M], Next[M], tot;
bool v[N];

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

void spfa() {
	queue<int> q;
	q.push(0);
	v[0] = 1;
	d[0] = 0;
	while (q.size()) {
		int x = q.front();
		q.pop();
		v[x] = 0;
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i];
			if (d[y] < d[x] + Leng[i]) {
				d[y] = d[x] + Leng[i];
				if (!v[y]) {
					v[y] = 1;
					q.push(y);
				}
			}
		}
	}
}

int main() {
	memset(d, 0xcf, sizeof(d));
	tot = m = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(x, y + 1, z);
		m = max(m, y + 1);
	}
	for (int i = 1; i <= m; i++) {
		add(i - 1, i, 0);
		add(i, i - 1, -1);
	}
	spfa();
	cout << d[m] << endl;
	return 0;
}
