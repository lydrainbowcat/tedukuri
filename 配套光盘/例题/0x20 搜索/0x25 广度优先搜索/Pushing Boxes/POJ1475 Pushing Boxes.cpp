//Author:XuHt
#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 26, INF = 0x3f3f3f3f;
char A[4] = {'N','S','W','E'};
char a[4] = {'n','s','w','e'};
int r, c, num = 0;
int d[4][2]= {{-1,0},{1,0},{0,-1},{0,1}};
char s[N][N];
string tmp;
struct P {
	int x, y, px, py;
	string ans;
};

bool pd(int x, int y) {
	return x > 0 && x <= r && y > 0 && y <= c && s[x][y] != '#';
}

bool bfs2(P p1, P p2) {
	tmp = "";
	P st;
	st.x = p1.px;
	st.y = p1.py;
	st.ans = "";
	queue<P> q;
	q.push(st);
	bool v[N][N];
	memset(v, 0, sizeof(v));
	while (q.size()) {
		P now = q.front(), nxt;
		q.pop();
		if (now.x == p1.x && now.y == p1.y) {
			tmp = now.ans;
			return 1;
		}
		for (int i = 0; i < 4; i++) {
			nxt = now;
			nxt.x = now.x + d[i][0];
			nxt.y = now.y + d[i][1];
			if (!pd(nxt.x, nxt.y)) continue;
			if (nxt.x == p2.x && nxt.y == p2.y) continue;
			if (v[nxt.x][nxt.y]) continue;
			v[nxt.x][nxt.y] = 1;
			nxt.ans = now.ans + a[i];
			q.push(nxt);
		}
	}
	return 0;
}

string bfs1() {
	P st;
	st.x = st.y = st.px = st.py = -1;
	st.ans = "";
	for (int i = 1; i <= r && (st.x == -1 || st.px == -1); i++)
		for (int j = 1; j <= c && (st.x == -1 || st.px == -1); j++)
			if (s[i][j] == 'B') {
				st.x = i;
				st.y = j;
				s[i][j] = '.';
			} else if (s[i][j] == 'S') {
				st.px = i;
				st.py = j;
				s[i][j] = '.';
			}
	queue<P> q;
	q.push(st);
	bool v[N][N][4];
	memset(v, 0, sizeof(v));
	string ans = "Impossible.";
	unsigned int cntans = INF, cnt = INF;
	while (q.size()) {
		P prv, now = q.front(), nxt;
		q.pop();
		if (s[now.x][now.y] == 'T') {
			unsigned int cntnow = 0;
			for (unsigned int i = 0; i < now.ans.length(); i++)
				if (now.ans[i] >= 'A' && now.ans[i] <= 'Z') ++cntnow;
			if (cntnow < cntans || (cntnow == cntans && now.ans.length() < cnt)) {
				ans = now.ans;
				cntans = cntnow;
				cnt = now.ans.length();
			}
			continue;
		}
		for (int i = 0; i < 4; i++) {
			nxt = now;
			nxt.x = now.x + d[i][0];
			nxt.y = now.y + d[i][1];
			if (!pd(nxt.x, nxt.y)) continue;
			if (v[nxt.x][nxt.y][i]) continue;
			prv = now;
			if (i == 3) prv.y = now.y - 1;
			else if (i == 2) prv.y = now.y + 1;
			else if (i == 1) prv.x = now.x - 1;
			else prv.x = now.x + 1;
			if (!bfs2(prv, now)) continue;
			v[nxt.x][nxt.y][i] = 1;
			nxt.ans = now.ans + tmp;
			nxt.ans = nxt.ans + A[i];
			nxt.px = now.x;
			nxt.py = now.y;
			q.push(nxt);
		}
	}
	return ans;
}

void Pushing_Boxes() {
	for (int i = 1; i <= r; i++) cin >> (s[i] + 1);
	cout << "Maze #" << ++num << endl << bfs1() << endl << endl;
}

int main() {
	while (cin >> r >> c && r && c) Pushing_Boxes();
	return 0;
}
