//Author:XuHt
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 60, INF = 0x3f3f3f3f;
int n, cnt[N], ans = 17;
struct P {
	int x, y, z;
	bool operator < (const P a) const {
		return z > a.z;
	}
};
vector<P> b;

int pd(int x, int y) {
	for (int i = x; i < N; i += y)
		if (!cnt[i]) return 0;
	return 1;
}

void dfs(int x, int now) {
	if (n <= 0) {
		ans = min(ans, now);
		return;
	}
	for (unsigned int i = x; i < b.size(); i++) {
		if (now + n / b[i].z >= ans) return;
		if (pd(b[i].x, b[i].y)) {
			for (int j = b[i].x; j < N; j += b[i].y) {
				cnt[j]--;
				n--;
			}
			dfs(i,now+1);
			for (int j = b[i].x; j < N; j += b[i].y) {
				cnt[j]++;
				n++;
			}
		}
	}
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		++cnt[a];
	}
	for (int i = 0; i < N / 2; i++)
		if (cnt[i])
			for (int j = i + 1; j < N - i; j++)
				if (pd(i, j)) {
					P p;
					p.x = i;
					p.y = j;
					p.z = (N - 1 - i) / j + 1;
					b.push_back(p);
				}
	sort(b.begin(), b.end());
	dfs(0, 0);
	cout << ans << endl;
	return 0;
}
