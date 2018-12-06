//Author:XuHt
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 20006, M = 106;
int n;
bool v[N+M][M];
struct P {
	int a, b, x;
} now, nxt;
queue<P> q;

bool add(int a, int b, int x) {
	if (a == n || b == n) return 1;
	if (a < b) swap(a, b);
	if (a == b || a >= n + 101 || b >= 101) return 0;
	if (v[a][b]) return 0;
	v[a][b] = 1;
	nxt.a = a;
	nxt.b = b;
	nxt.x = x;
	q.push(nxt);
	return 0;
}

int main() {
	cin >> n;
	add(1, 0, 0);
	int a, b, x;
	while (q.size()) {
		now = q.front();
		q.pop();
		a = now.a;
		b = now.b;
		x = now.x + 1;
		if (add(a + a, b, x)) {
			cout << x << endl;
			break;
		}
		if (add(a, b + b, x)) {
			cout << x << endl;
			break;
		}
		if (add(a, a + b, x)) {
			cout << x << endl;
			break;
		}
		if (add(b, a + b, x)) {
			cout << x << endl;
			break;
		}
		if (add(a, a + a, x)) {
			cout << x << endl;
			break;
		}
		if (add(b, b + b, x)) {
			cout << x << endl;
			break;
		}
		if (add(a - b, b, x)) {
			cout << x << endl;
			break;
		}
		if (add(a, a - b, x)) {
			cout << x << endl;
			break;
		}
	}
	return 0;
}
