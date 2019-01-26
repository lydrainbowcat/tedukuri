//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1006;
int n, r[N], c[N], d[N], s[N];
int Head[N], Edge[N], Next[N], Leng[N], tot;
queue<int> q;
bool v[N];

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

inline int spfa(int now) {
	for (int i = 1; i <= 7; i++) Leng[Head[i]] = now - r[i];
	Leng[Head[24]] = -now;
	memset(d, 0x3f, sizeof(d));
	memset(s, 0, sizeof(s));
	queue<int> nq;
	swap(q, nq);
	for (int i = 0; i <= 24; i++) {
		q.push(i);
		d[i] = 0;
		v[i] = 1;
	}
	while (q.size()) {
		int x = q.front();
		q.pop();
		v[x] = 0;
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i], z = Leng[i];
			if(d[y] > d[x] + z) {
				d[y] = d[x] + z;
				s[y] = s[x] + 1;
				if (s[y] > 25) return 0;
				if (!v[y]) {
					q.push(y);
					v[y] = 1;
				}
			}
		}
	}
	return 1;
}

inline void Cashier_Employment() {
	for (int i = 1; i <= 24; i++) scanf("%d", &r[i]);
	cin >> n;
	tot = 0;
	memset(Head, 0, sizeof(Head));
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		c[x+1]++;
	}
	for (int i = 1; i <= 24; i++) {
		add(i - 1, i, c[i]);
		add(i, i - 1, 0);
	}
	for (int i = 8; i <= 24; i++) add(i, i - 8, -r[i]);
	for (int i = 1; i <= 7; i++) add(i, i + 16, 0);
	add(24, 0, 0);
	for (int i = 1; i <= n; i++)
		if (spfa(i)) {
			cout << i << endl;
			return;
		}
	puts("No Solution");
}

int main() {
	int t;
	cin >> t;
	while (t--) Cashier_Employment();
	return 0;
}
