//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1006, M = 5006;
const double eps = 1e-6;
int n, m, c[N], f[N], x[M], y[M], z[M];
int Head[N], Edge[M], Next[M], tot;
double Leng[M], d[N];
bool v[N];

void add(int x, int y, double z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
}

bool spfa() {
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		q.push(i);
		d[i] = 0;
		v[i] = 1;
	}
	memset(c, 0, sizeof(c));
	while (q.size()) {
		int x = q.front();
		q.pop();
		v[x] = 0;
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Edge[i];
			if (d[y] > d[x] + Leng[i]) {
				d[y] = d[x] + Leng[i];
				if (++c[y] > n) return 1;
				if (!v[y]) {
					q.push(y);
					v[y] = 1;
				}
			}
		}
	}
	return 0;
}

bool pd(double w) {
	tot = 0;
	memset(Head, 0, sizeof(Head));
	for (int i = 1; i <= m; i++)
		add(x[i], y[i], w * z[i] - f[x[i]]);
	return spfa();
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		scanf("%d", &f[i]);
	for (int i = 1; i <= m; i++)
		scanf("%d %d %d", &x[i], &y[i], &z[i]);
	double l = 0, r = 1000;
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (pd(mid)) l = mid;
		else r = mid;
	}
	printf("%.2f", l);
	return 0;
}
