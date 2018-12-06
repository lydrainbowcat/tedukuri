#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int c[20], cab[20], n, w, ans;
void dfs(int now, int cnt) {
	if (cnt >= ans) return;
	if (now == n+1) {
		ans = min(ans, cnt);
		return;
	}
	for (int i = 1; i <= cnt; i++) {  // 分配到已租用缆车
		if (cab[i] + c[now] <= w) {   // 能装下
			cab[i] += c[now];
			dfs(now+1, cnt);
			cab[i] -= c[now];         // 还原现场
		}
	}
	cab[cnt+1] = c[now];
	dfs(now+1, cnt+1);
	cab[cnt+1] = 0;
}
int main() {
	cin >> n >> w;
	for (int i = 1; i <= n; i++) cin >> c[i];
	sort(c + 1, c + n + 1);
	reverse(c + 1, c + n + 1);
	ans = n;    // 最多用n辆缆车，每只猫一辆
	dfs(1, 0);  // 搜索入口
	cout << ans << endl;
}