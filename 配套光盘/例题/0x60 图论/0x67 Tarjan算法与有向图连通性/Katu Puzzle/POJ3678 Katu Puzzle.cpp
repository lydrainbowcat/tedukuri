//Author:XuHt
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006;
int n, m, dfn[N], low[N], num, st[N], top, c[N], cnt;
bool ins[N];
vector<int> e[N<<1];

inline void add(int x, int y) {
	e[x].push_back(y);
}

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	st[++top] = x;
	ins[x] = 1;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (ins[y])
			low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x]) {
		++cnt;
		int y;
		do {
			y = st[top--];
			ins[y] = 0;
			c[y] = cnt;
		} while (x != y);
	}
}

int main() {
	cin >> n >> m;
	while (m--) {
		int a, b, c;
		char s[6];
		scanf("%d %d %d %s", &a, &b, &c, s);
		if (s[0] == 'A') {
			if (c) {
				add(a, a + n);
				add(b, b + n);
			} else {
				add(a + n, b);
				add(b + n, a);
			}
		} else if (s[0] == 'O') {
			if (c) {
				add(a, b + n);
				add(b, a + n);
			} else {
				add(a + n, a);
				add(b + n, b);
			}
		} else {
			if (c) {
				add(a, b + n);
				add(b, a + n);
				add(a + n, b);
				add(b + n, a);
			} else {
				add(a, b);
				add(b, a);
				add(a + n, b + n);
				add(b + n, a + n);
			}
		}
	}
	for (int i = 0; i < n; i++)
		if (!dfn[i]) tarjan(i);
	for (int i = 0; i < n; i++)
		if (c[i] == c[i+n]) {
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}
