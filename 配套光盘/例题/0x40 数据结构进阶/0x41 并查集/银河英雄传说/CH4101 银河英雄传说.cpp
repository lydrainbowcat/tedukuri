//Author:XuHt
#include <cmath>
#include <iostream>
using namespace std;
const int N = 30001;
int fa[N], d[N], s[N];

int get(int x) {
	if (x == fa[x]) return x;
	int root = get(fa[x]);
	d[x] += d[fa[x]];
	return fa[x] = root;
}

int main() {
	int t;
	cin >> t;
	for (int i = 1; i < N; i++) {
		fa[i] = i;
		s[i] = 1;
		d[i] = 0;
	}
	while (t--) {
		char c;
		cin >> c;
		int x, y;
		cin >> x >> y;
		int m = get(x), n = get(y);
		if (c == 'M') {
			fa[m] = n;
			d[m] = s[n];
			s[n] += s[m];
		} else {
			if (m == n) cout << abs(d[x] - d[y]) - 1 << endl;
			else cout << "-1" << endl;
		}
	}
	return 0;
}
