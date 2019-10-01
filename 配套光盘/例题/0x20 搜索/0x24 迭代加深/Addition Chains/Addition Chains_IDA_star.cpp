#include <bits/stdc++.h>
using namespace std;
int n, a[20], depth, lg[110];
int hfunc(int now) {
	if (a[now] > n) return 1e5;
	return lg[int(ceil(n / a[now]))]; 
}
int calc(int x) {
	int l = 0, r = 30;
	while (l < r) {
		int mid = (l + r) >> 1;
		if ((1 << mid) >= x) r = mid;
		else l = mid + 1;
	}
	return l;
}
bool dfs(int now) {
	if (now + hfunc(now) > depth || 1ll * a[now] * (1 << (depth - now + 1)) < n) return 0;
	if (now == depth) return a[now] == n;
	for (register int i = now; i; --i) {
		int num = a[now] + a[i];
		if (num <= n) {
			a[now + 1] = num;
			if (dfs(now + 1)) return 1;
		}
	}	
	return 0;
}
int main() {
	a[1] = 1;
	a[2] = 2;
	for (register int i = 1; i < 110; ++i)
		lg[i] = calc(i); 
	while (cin >> n && n) {
		depth = 2;
		if (n == 1) {
		    puts("1");
		    continue;
		}
		while (!dfs(2)) ++depth;
		for (register int i = 1; i <= depth; ++i) printf("%d ", a[i]);
		puts("");
	}
}
