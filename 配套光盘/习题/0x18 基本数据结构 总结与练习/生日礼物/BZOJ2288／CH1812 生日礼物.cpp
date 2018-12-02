//Author:XuHt
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 100006;
int n, m, a[N], s[N], nxt[N], prv[N];
bool v[N];
struct P {
	int p, c;
	bool operator < (const P x) const {
		return abs((double)c) > abs((double)x.c);
	}
};
priority_queue<P> q;

void Delete(int x) {
	v[x] = 0;
	prv[nxt[x]] = prv[x];
	nxt[prv[x]] = nxt[x];
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int tot = 1;
	for (int i = 1; i <= n; i++)
		if ((ll)s[tot] * a[i] >= 0) s[tot] += a[i];
		else s[++tot] = a[i];
	int ans = 0, cnt = 0;
	for (int i = 1; i <= tot; i++) {
		P p;
		p.c = s[i];
		p.p = i;
		q.push(p);
		if (s[i] > 0) {
			ans += s[i];
			cnt++;
		}
		prv[i] = i - 1;
		nxt[i] = i + 1;
	}
	memset(v, 1, sizeof(v));
	while (cnt > m) {
		cnt--;
		P p = q.top();
		while (!v[p.p]) {
			q.pop();
			p = q.top();
		}
		q.pop();
		if (prv[p.p] && nxt[p.p] != tot + 1) ans -= abs((double)s[p.p]);
		else if (s[p.p] > 0) ans -= s[p.p];
		else {
			cnt++;
			continue;
		}
		s[p.p] += s[prv[p.p]] + s[nxt[p.p]];
		Delete(prv[p.p]);
		Delete(nxt[p.p]);
		p.c = s[p.p];
		q.push(p);
	}
	cout << ans << endl;
	return 0;
}
