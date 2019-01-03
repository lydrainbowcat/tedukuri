//Author:XuHt
#include <cmath>
#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2006, INF = 0x3f3f3f3f;
int n, k, a[N], f[N][N], d[N][N];
priority_queue<int> q1;
priority_queue<int, vector<int>, greater<int> > q2;

void Estimation() {
	k = min(k, n);
	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) {
		priority_queue<int> empty1;
		priority_queue<int, vector<int>, greater<int> > empty2;
		swap(empty1, q1);
		swap(empty2, q2);
		int s = 0, c = 0;
		for (int j = i; j < n; j++) {
			if (q1.empty() || a[j] <= q1.top()) {
				q1.push(a[j]);
				s -= a[j];
			} else {
				q2.push(a[j]);
				s += a[j];
			}
			unsigned int k1 = ++c >> 1, k2 = c - k1;
			if (q1.size() > k1) {
				q2.push(q1.top());
				s += q1.top() << 1;
				q1.pop();
			}
			if (q2.size() > k2) {
				q1.push(q2.top());
				s -= q2.top() << 1;
				q2.pop();
			}
			while (q1.size() && q2.size() && q2.top() < q1.top()) {
				int x1 = q1.top(), x2 = q2.top();
				q1.pop();
				q2.pop();
				q1.push(x2);
				s -= x2 << 1;
				q2.push(x1);
				s += x1 << 1;
			}
			int w = s;
			if (q2.size() > q1.size()) w -= q2.top();
			d[i][j+1] = abs(w);
		}
	}
	f[0][0] = 0;
	for (int i = 0; i < k; i++)
		for (int j = 0; j < n; j++)
			if (f[i][j] != INF)
				for (int p = j + 1; p <= n; p++)
					f[i+1][p] = min(f[i+1][p], f[i][j] + d[j][p]);
	cout << f[k][n] << endl;
}

int main() {
	while (cin >> n >> k && n) Estimation();
	return 0;
}
