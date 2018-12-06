//Author:XuHt
#include <queue>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 30006;
int num[N], ans[N];
vector<int> e[N], a;
bitset<N> b[N];
queue<int> q;

int main() {
	memset(num, 0, sizeof(num));
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		e[x].push_back(y);
		num[y]++;
		b[x][y] = 1;
	}
	for (int i = 1; i <= n; i++) if (!num[i]) q.push(i);
	while (q.size()) {
		int x = q.front();
		q.pop();
		a.push_back(x);
		for (unsigned int i = 0; i < e[x].size(); i++) {
			int y = e[x][i];
			if (!--num[y]) q.push(y);
		}
	}
	for (int i = 1; i <= n; i++) b[i][i] = 1;
	for (int i = a.size() - 1; i >= 0; i--) {
		int x = a[i];
		for (unsigned int j = 0; j < e[x].size(); j++)
			b[x] |= b[e[x][j]];
		ans[x] = b[x].count();
	}
	for(int i = 1; i <= n; i++) cout << ans[i] << endl;
	return 0;
}
