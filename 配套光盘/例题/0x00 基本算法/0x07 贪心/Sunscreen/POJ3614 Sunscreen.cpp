//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2506;
int n, m;
struct COW {
	int l, r;
	bool operator < (const COW x) const {
		return l > x.l;
	}
} cow[N];
struct SPF {
	int s, c;
	bool operator < (const SPF x) const {
		return s > x.s;
	}
} spf[N];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d %d", &cow[i].l, &cow[i].r);
	for (int i = 1; i <= m; i++) scanf("%d %d", &spf[i].s, &spf[i].c);
	sort(cow + 1, cow + n + 1);
	sort(spf + 1, spf + m + 1);
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (spf[j].c && spf[j].s >= cow[i].l && spf[j].s <= cow[i].r) {
				ans++;
				spf[j].c--;
				break;
			}
	cout << ans << endl;
	return 0;
}
