//Author:XuHt
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 50006;
int fa[3*N];

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

int main() {
	int n, k, ans = 0;
	cin >> n >> k;
	for (int i = 1; i <= 3 * n; i++) fa[i] = i;
	while (k--) {
		int num, x, y;
		scanf("%d %d %d", &num, &x, &y);
		if (x > n || y > n || (num == 2 && x == y)) {
			++ans;
			continue;
		}
		if (num == 1 && (get(x) == get(y + n) || get(x + n) == get(y))) {
			++ans;
			continue;
		}
		if (num == 2 && (get(x) == get(y) || get(x) == get(y + n))) {
			++ans;
			continue;
		}
		if (num == 1) {
			fa[get(x)] = get(y);
			fa[get(x+n)] = get(y + n);
			fa[get(x+2*n)] = get(y + 2 * n);
		} else {
			fa[get(x+n)] = get(y);
			fa[get(x+2*n)] = get(y + n);
			fa[get(x)] = get(y + 2 * n);
		}
	}
	cout << ans << endl;
	return 0;
}
