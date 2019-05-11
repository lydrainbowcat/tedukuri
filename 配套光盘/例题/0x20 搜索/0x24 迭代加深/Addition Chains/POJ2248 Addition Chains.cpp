//Author:XuHt
#include <cstring>
#include <iostream>
using namespace std;
const int N = 106;
int n, ans[N], dep;

bool dfs(int now) {
	if (now == dep) return ans[now] == n;
	bool v[N];
	memset(v, 0, sizeof(v));
	for (int i = now; i; i--)
		for (int j = i; j; j--) {
			int num = ans[i] + ans[j];
			if (num <= n && num > ans[now] && !v[num]) {
				ans[now+1] = num;
				if (dfs(now + 1)) return 1;
				else v[num] = 1;
			}
		}
	return 0;
}

int main() {
	ans[1] = 1;
	while (cin >> n && n) {
		dep = 1;
		while (!dfs(1)) ++dep;
		for (int i = 1; i <= dep; i++) cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}
