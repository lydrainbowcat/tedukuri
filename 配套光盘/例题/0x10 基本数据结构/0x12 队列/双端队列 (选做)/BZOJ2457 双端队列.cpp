//Author:XuHt
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006, INF = 0x3f3f3f3f;
pair<int, int> a[N];
int n;
vector<int> p[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].first);
		a[i].second = i;
	}
	sort(a + 1, a + n + 1);
	int t = 0;
	for (int i = 1; i <= n; i++) {
		p[++t].push_back(a[i].second);
		while (a[i].first == a[i+1].first)
			p[t].push_back(a[++i].second);
	}
	for (int i = 1; i <= t; i++) sort(p[i].begin(), p[i].end());
	bool flag = 0;
	int num = INF, ans = 1;
	for (int i = 1; i <= t; i++) {
		int s = p[i].size();
		if (flag) {
			if (num < p[i][0]) num = p[i][s-1];
			else {
				++ans;
				flag = 0;
				num = p[i][0];
			}
		}
		else {
			if (num > p[i][s-1]) num = p[i][0];
			else {
				flag = 1;
				num = p[i][s-1];
			}
		}
	}
	cout << ans << endl;
	return 0;
}
