//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50006, INF = 0x3f3f3f3f;
struct P {
	int x, y;
	bool operator < (const P w) const {
		return x + y < w.x + w.y;
	}
} p[N];
int n;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d %d", &p[i].x, &p[i].y);
	sort(p + 1, p + n + 1);
	int ans = -INF, k = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, k - p[i].y);
		k += p[i].x;
	}
	cout << ans << endl;
	return 0;
}
