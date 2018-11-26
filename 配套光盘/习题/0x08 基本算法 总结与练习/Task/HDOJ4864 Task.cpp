//Author:XuHt
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 100006, M = 106;
struct P {
	int x, y;
	bool operator < (const P w) const {
		return x > w.x || (x == w.x && y > w.y);
	}
} p[N];
vector<int> t[M];
int n, m;

bool cmp(int x, int y) {
	return x > y;
}

void Task() {
	for (int i = 0; i <= 100; i++) t[i].clear();
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		t[y].push_back(x);
	}
	for (int i = 0; i <= 100; i++) sort(t[i].begin(), t[i].end(), cmp);
	for (int i = 1; i <= m; i++) scanf("%d %d", &p[i].x, &p[i].y);
	sort(p + 1, p + m + 1);
	int ans = 0;
	ll ansa = 0;
	for (int i = 1; i <= m; i++) {
		bool flag = 0;
		for (int j = p[i].y; j <= 100; j++) {
			int s = t[j].size();
			bool ok = 0;
			for (int k = s - 1; k >= 0; k--)
				if (t[j][k] >= p[i].x) {
					t[j].erase(t[j].begin() + k);
					ok = 1;
					break;
				}
			if (ok) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			ans++;
			ansa += 500 * p[i].x + 2 * p[i].y;
		}
	}
	cout << ans << " " << ansa << endl;
}

int main() {
	while (cin >> n >> m) Task();
	return 0;
}
