//Author:xht37
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 6, M = 1e6 + 6;
int n, m, tot, Price[N], Ans;
int Head[N], Side[M], Next[M], ans[N];
int fHead[N], fSide[M], fNext[M], fans[N];
priority_queue<pair<int, int> > q;
priority_queue<pair<int, int> > fq;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d", &Price[i]);
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		Side[++tot] = y;
		Next[tot] = Head[x];
		Head[x] = tot;
		fSide[tot] = x;
		fNext[tot] = fHead[y];
		fHead[y] = tot;
		if (z == 2) {
			Side[++tot] = x;
			Next[tot] = Head[y];
			Head[y] = tot;
			fSide[tot] = y;
			fNext[tot] = fHead[x];
			fHead[x] = tot;
		}
	}
	memset(ans, 0x3f, sizeof(ans));
	memset(fans, 0xcf, sizeof(fans));
	ans[1] = Price[1];
	fans[n] = Price[n];
	q.push(make_pair(-ans[1], 1));
	fq.push(make_pair(fans[n], n));
	while (q.size()) {
		int x = q.top().second;
		q.pop();
		for (int i = Head[x]; i; i = Next[i]) {
			int y = Side[i];
			if (ans[y] > ans[x]) {
				ans[y] = ans[x];
				ans[y] = min(ans[y], Price[y]);
				q.push(make_pair(-ans[y], y));
			}
		}
	}
	while (fq.size()) {
		int x = fq.top().second;
		fq.pop();
		for (int i = fHead[x]; i; i = fNext[i]) {
			int y = fSide[i];
			if (fans[y] < fans[x]) {
				fans[y] = fans[x];
				fans[y] = max(fans[y], Price[y]);
				fq.push(make_pair(fans[y], y));
			}
		}
	}
	for (int i = 1; i <= n; i++) Ans = max(Ans, fans[i]-ans[i]);
	cout << Ans << endl;
	return 0;
}
