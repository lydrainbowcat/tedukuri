//Author:XuHt
#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10006;
int n;
pair<int, int> a[N];
priority_queue<int> q;

void Supermarket() {
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i].second, &a[i].first);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		if (a[i].first == q.size() && -q.top() < a[i].second) {
			q.pop();
			q.push(-a[i].second);
			continue;
		}
		if (a[i].first > q.size()) q.push(-a[i].second);
	}
	int ans = 0;
	while (q.size()) {
		ans += q.top();
		q.pop();
	}
	cout << -ans << endl;
}

int main() {
	while (cin >> n) Supermarket();
	return 0;
}
