//Author:XuHt
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 50006, M = 200006, INF = 0x3f3f3f3f;
const double eps = 1e-3;
int n, m, st, ed, t;
int Head[N], Edge[M], Next[M], tot;
double d[N], s[N], Leng[M];
bool v[N];

inline void add(int x, int y) {
	Edge[++tot] = y;
	Next[tot] = Head[x];
	Head[x] = tot;
}

inline int f(char ch) {
	switch (ch) {
		case 'S':
			t = 0;
			return 1000;
		case 'G':
			t = 1;
			return 500;
		case 'D':
			t = 2;
			return 300;
		case 'T':
			t = 3;
			return 200;
		case 'K':
			t = 4;
			return 150;
	}
	return -1;
}

bool dfs(int x) {
	v[x] = 1;
	for (int i = Head[x]; i; i = Next[i]) {
		int y = Edge[i];
		double z = Leng[i];
		if (d[y] > d[x] + z) {
			d[y] = d[x] + z;
			if (v[y] || dfs(y)) return 1;
		}
	}
	v[x] = 0;
	return 0;
}

inline bool pd(double x) {
	for (int i = 1; i <= m; i++) Leng[i] = x - s[i];
	memset(v, 0, sizeof(v));
	memset(d, 0x3f, sizeof(d));
	for (int i = 1; i <= 50000; i++)
		if (dfs(i)) return 1;
	return 0;
}

int main() {
	cin >> m;
	for (int i = 1; i <= m; i++) {
		string str;
		cin >> str;
		n = str.length();
		int x = 0;
		bool flag = 0;
		for (int j = 0; j < n; j++) {
			if (str[j] >= '0' && str[j] <= '9')
				x = x * 10 + str[j] - '0';
			else if (str[j] == '-') {
				if (!flag) st = x + t * 10000;
				flag = 1;
				x = 0;
			} else s[i] += f(str[j]);
		}
		ed = x + t * 10000;
		add(st, ed);
	}
	double l = 0, r = INF, ans = -1;
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (pd(mid)) {
			l = mid;
			ans = mid;
		} else r = mid;
	}
	printf("%.0lf\n", ans);
	return 0;
}
