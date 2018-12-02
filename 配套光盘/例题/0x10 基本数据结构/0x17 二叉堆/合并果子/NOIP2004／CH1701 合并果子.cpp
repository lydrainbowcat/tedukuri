//Author:XuHt
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
priority_queue<int> q;

int main() {
	int n, a;
	cin >> n;
	while (n--) {
		scanf("%d", &a);
		q.push(-a);
	}
	int ans = 0;
	while (q.size() != 1) {
		int x = -q.top();
		q.pop();
		int y = -q.top();
		q.pop();
		ans += x + y;
		q.push(- x - y);
	}
	cout << ans << endl;
	return 0;
}
