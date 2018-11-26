//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006, INF = 0x3f3f3f3f;
int n, s[N], e[N], d[N];

int f(int a, int b, int c) {
	return (b >= a) ? ((b - a) / c + 1) : 0;
}

int get(int r) {
	int ans = 0;
	for (int i = 1; i <= n; i++) ans += f(s[i], min(e[i], r), d[i]);
	return ans;
}

void fx() {
	cin >> n;
	int mins = INF, maxe = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &s[i], &e[i], &d[i]);
		mins = min(mins, s[i]);
		maxe = max(maxe, e[i]);
	}
	if (get(maxe) % 2 == 0) {
		cout << "There's no weakness." << endl;
		return;
	}
	int l = mins, r = maxe;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (get(mid) % 2) r = mid;
		else l = mid + 1;
	}
	cout << l << " " << get(l) - get(l - 1) << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) fx();
	return 0;
}
