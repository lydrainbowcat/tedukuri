//Author:XuHt
#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 30006;
int a[N];
priority_queue<int> q1, q2;

int main() {
	int m, n;
	cin >> m >> n;
	for (int i = 0; i < m; i++) scanf("%d", &a[i]);
	int t = 0;
	while (n--) {
		int k;
		scanf("%d", &k);
		while (t < k) {
			q2.push(-a[t]);
			if (q1.size() && q1.top() > -q2.top()) {
				int x = q1.top(), y = -q2.top();
				q1.pop();
				q2.pop();
				q1.push(y);
				q2.push(-x);
			}
			t++;
		}
		cout << -q2.top() << endl;
		q1.push(-q2.top());
		q2.pop();
	}
	return 0;
}
