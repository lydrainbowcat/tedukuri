//Author:XuHt
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, w = INF, cnt = 0;
struct P {
	int t, m, p, s;
	bool operator < (const P x) const {
		return s < x.s;
	}
} x;
vector<P> p;
queue<P> q;

bool work_in(int t) {
	if (p.empty() || p[0].s >= x.m) {
		x.s = 0;
		x.t = t;
		p.push_back(x);
		sort(p.begin(), p.end());
		return 1;
	}
	for (unsigned int i = 1; i < p.size(); i++)
		if (p[i].s - (p[i-1].s + p[i-1].m) >= x.m) {
			x.s = p[i-1].s + p[i-1].m;
			x.t = t;
			p.push_back(x);
			sort(p.begin(), p.end());
			return 1;
		}
	int sz = p.size();
	if (n - (p[sz-1].s + p[sz-1].m) >= x.m) {
		x.s = p[sz-1].s + p[sz-1].m;
		x.t = t;
		p.push_back(x);
		sort(p.begin(), p.end());
		return 1;
	}
	return 0;
}

void work_out() {
	int nw = INF;
	for (unsigned int i = 0; i < p.size(); i++)
		if (p[i].t + p[i].p == w) p.erase(p.begin() + i--);
		else nw = min(nw, p[i].t + p[i].p);
	while (q.size()) {
		x = q.front();
		if (work_in(w)) {
			nw = min(nw, q.front().t + q.front().p);
			q.pop();
			cnt++;
		} else break;
	}
	w = nw;
}

void work(int t, int m, int p) {
	while (t >= w) work_out();
	x.t = t;
	x.m = m;
	x.p = p;
	if (work_in(t)) w = min(w, t + p);
	else q.push(x);
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	int t0, m0, p0;
	while (cin >> t0 >> m0 >> p0 && !(!t0 && !m0 && !p0))
		work(t0, m0, p0);
	while (q.size())
		work_out();
	int ans = w;
	for (unsigned int i = 0; i < p.size(); i++)
		ans = max(ans, p[i].t + p[i].p);
	cout << ans << endl << cnt << endl;
	return 0;
}
