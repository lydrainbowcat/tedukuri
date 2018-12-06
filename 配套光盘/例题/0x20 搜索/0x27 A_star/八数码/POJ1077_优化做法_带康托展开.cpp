//Author:XuHt
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 362886;
int fa[N], f[N];
bool v[N];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};
int jc[10] = {1,1,2,6,24,120,720,5040,40320,362880};
struct P {
	int i, x, y;
	string s;
	bool operator < (const P a) const {
		return x + y > a.x + a.y;
	}
};
priority_queue<P> q;

int cantor(string st) {
	int len = st.size();
	for (int i = 0; i < len; i++)
		if (st[i] == 'x') {
			st[i] = '0';
			break;
		}
	int ans = 1;
	for (int i = 0; i < len; i++) {
		int num = 0;
		for (int j = 0; j < i; j++) if (st[j] < st[i]) ++num;
		ans += (st[i] - '0' - num) * jc[len-i-1];
	}
	return ans;
}

int S(string s) {
	int ans = 0;
	for (unsigned int i = 0; i < s.size(); i++) {
		int r = i / 3, c = i % 3;
		if (s[i] == 'x') ans += abs(r - 2) + abs(c - 2);
		else {
			int k = s[i] - '1';
			ans += abs(r - k / 3) + abs(c - k % 3);
		}
	}
	return ans;
}

bool bfs(string st) {
	string ed = "12345678x";
	memset(v, 0, sizeof(v));
	memset(fa, -1, sizeof(fa));
	memset(f, -1, sizeof(f));
	int k;
	for (int i = 0; i < 10; i++)
		if (st[i] == 'x') {
			k = i;
			break;
		}
	P p;
	p.i = k;
	p.x = 1;
	p.y = S(st);
	p.s = st;
	q.push(p);
	v[cantor(st)] = 1;
	while (q.size()) {
		p = q.top();
		if (p.s == ed) return 1;
		q.pop();
		int r = p.i / 3, c = p.i % 3;
		for (int i = 0; i < 4; i++) {
			int nx = r + dx[i], ny = c + dy[i];
			if (nx < 0 || nx > 2 || ny < 0 || ny > 2) continue;
			string s = p.s;
			swap(s[p.i], s[nx*3+ny]);
			if (v[cantor(s)]) continue;
			v[cantor(s)] = 1;
			fa[cantor(s)] = cantor(p.s);
			f[cantor(s)] = i;
			P np;
			np.i = nx * 3 + ny;
			np.x = p.x + 1;
			np.y = S(s);
			np.s = s;
			q.push(np);
		}
	}
	return 0;
}

int main() {
	string st = "";
	for (int i = 1; i < 10; i++) {
		char s[2];
		cin >> s;
		st += s[0];
	}
	int cnt = 0;
	for (unsigned i = 0; i < st.size(); i++)
		if (st[i] != 'x')
			for (unsigned int j = 0; j < i; j++)
				if (st[j] != 'x' && st[j] > st[i]) ++cnt;
	if (cnt & 1) {
		cout << "unsolvable" << endl;
		return 0;
	}
	vector<int> ans;
	if (bfs(st)) {
		int k = cantor("12345678x");
		while (k != -1) {
			ans.push_back(f[k]);
			k = fa[k];
		}
		for (unsigned int i = ans.size() - 1; i < ans.size(); i--)
			if (ans[i] == 0) putchar('u');
			else if (ans[i] == 1) putchar('l');
			else if (ans[i] == 2) putchar('d');
			else if (ans[i] == 3) putchar('r');
	} else puts("unsolvable");
	return 0;
}
