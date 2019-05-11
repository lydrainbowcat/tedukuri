//Author:xht37
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 100;
struct P {
	int x1, x2, y1, y2;
} p[N];
vector<int> e[N];
int n, xx, yy, f[N], s[N], num, now;
bitset<N> v;

bool dfs(int x) {
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (v[y] || (x == xx && y == yy)) continue;
		v[y] = 1;
		if (!f[y] || dfs(f[y])) {
			f[y] = x;
			s[x] = y;
			return 1;
		}
	}
	return 0;
}

inline int work() {
	int ret = 0;
	memset(f, 0, sizeof(f));
	memset(s, 0, sizeof(s));
	for (int i = 1; i <= n; i++) {
		v.reset();
		ret += dfs(i);
	}
	return ret;
}

void print() {
	bool flag = 0;
	int t[N];
	for (int i = 1; i <= n; i++) t[i] = s[i];
	for (int i = 1; i <= n; i++) {
		if (t[i] == -1) continue;
		xx = i, yy = t[i];
		if (work() != now) {
			if (flag) printf(" ");
			printf("(%c,%d)", 'A' + i - 1, t[i]);
			flag = 1;
		}
	}
	puts(flag ? "" : "none");
}

inline void Sorting_Slides() {
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d %d", &p[i].x1, &p[i].x2, &p[i].y1, &p[i].y2);
		e[i].clear();
	}
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		for (int j = 1; j <= n; j++)
			if (x >= p[j].x1 && x <= p[j].x2 && y >= p[j].y1 && y <= p[j].y2)
				e[j].push_back(i);
	}
	xx = -1, yy = -1;
	now = work();
	printf("Heap %d\n", ++num);
	print();
	puts("");
}

int main() {
	while (cin >> n && n) Sorting_Slides();
	return 0;
}
