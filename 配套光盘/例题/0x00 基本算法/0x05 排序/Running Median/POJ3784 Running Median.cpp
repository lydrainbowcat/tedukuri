//Author:XuHt
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
priority_queue<int> q1, q2;

void Running_Median() {
	while (q1.size()) q1.pop();
	while (q2.size()) q2.pop();
	int num, n;
	cin >> num >> n;
	cout << num << " " << (n + 1) / 2 << endl;
	int a;
	cin >> a;
	cout << a << " ";
	q2.push(-a);
	int cnt = 1;
	for (int i = 2; i <= n; i++) {
		scanf("%d", &a);
		if (a < -q2.top()) q1.push(a);
		else q2.push(-a);
		int s = q1.size();
		if (s > i / 2) {
			q2.push(-q1.top());
			q1.pop();
		}
		if (s < i / 2) {
			q1.push(-q2.top());
			q2.pop();
		}
		if (i % 2) {
			cout<< -q2.top() << " ";
			if (++cnt % 10 == 0) cout << endl;
		}
	}
	cout << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) Running_Median();
	return 0;
}
