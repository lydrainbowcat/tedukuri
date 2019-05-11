//Author:XuHt
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10006;
int n, fa[N];
pair<int, int> p[N];

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

void Supermarket() {
	int d = 0, ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> p[i].first >> p[i].second;
		d = max(d, p[i].second);
	}
	for (int i = 0; i <= d; i++) fa[i] = i;
	sort(p + 1, p + n + 1);
	for (int i = n; i; i--) {
		int x = get(p[i].second);
		if (x) {
			ans += p[i].first;
			fa[x] = x - 1;
		}
	}
	cout << ans << endl;
}

int main() {
	while (cin >> n) Supermarket();
	return 0;
}
