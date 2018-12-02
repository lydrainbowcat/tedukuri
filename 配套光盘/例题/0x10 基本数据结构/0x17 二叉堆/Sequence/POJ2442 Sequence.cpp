//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2006;
int m, n, f[N], a[N], b[N];
priority_queue<pair<int, pair<int, int> > > q;

void work() {
	priority_queue<pair<int, pair<int, int> > > w;
	swap(w, q);
	q.push(make_pair(- a[1] - b[1], make_pair(1, 1)));
	for (int i = 1; i <= n; i++) {
		f[i] = -q.top().first;
		int x = q.top().second.first, y = q.top().second.second;
		q.pop();
		if (y == 1) q.push(make_pair(- a[x+1] - b[y], make_pair(x + 1, y)));
		q.push(make_pair(- a[x] - b[y+1], make_pair(x, y + 1)));
	}
}

void Sequence() {
	cin >> m >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	--m;
	while (m--) {
		for (int j = 1; j <= n; j++) scanf("%d", &b[j]);
		sort(b + 1, b + n + 1);
		work();
		memcpy(a, f, sizeof(a));
	}
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);
	cout << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) Sequence();
	return 0;
}
