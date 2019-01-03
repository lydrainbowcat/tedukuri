//Author:XuHt
#include <cstring>
#include <iostream>
using namespace std;
const int N = 56;
int f[N][N][N], b[N];

int dfs(int p, int x, int y, bool o, bool k) {
	if (!p) return k || x >= y;
	if (!k && !o && f[p][x][y] != -1) return f[p][x][y];
	int z = o ? b[p] : 1, ans = 0;
	for (int i = 0; i <= z; i++)
		if (k) {
			if (i) ans += dfs(p - 1, x, y + 1, o && z == i, 0);
			else ans += dfs(p - 1, 0, 0, o && z == i, 1);
		} else {
			if (i) ans += dfs(p - 1, x, y + 1, o && z == i, 0);
			else ans += dfs(p - 1, x + 1, y, o && z == i, 0);
		}
	if (!o && !k) f[p][x][y] = ans;
	return ans;
}

int work(int n) {
	int i = 0;
	while (n) {
		b[++i] = n & 1;
		n >>= 1;
	}
	return dfs(i, 0, 0, 1, 1);
}

int main() {
	memset(f, -1, sizeof(f));
	int l, r;
	while (cin >> l >> r) cout << work(r) - work(l - 1) << endl;
	return 0;
}
