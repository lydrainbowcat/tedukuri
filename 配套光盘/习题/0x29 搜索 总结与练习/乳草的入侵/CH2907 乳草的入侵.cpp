//Author:XuHt
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 106;
int x, y, mx, my, d[N][N];
char s[N][N];
bool v[N][N];
int dx[8]= {-1,-1,-1,1,1,1,0,0};
int dy[8]= {-1,0,1,-1,0,1,-1,1};
queue<pair<int, int> > q;

bool pd() {
	for (int i = 1; i <= y; i++)
		for (int j = 1; j <= x; j++)
			if (!v[i][j]) return 0;
	return 1;
}

int main() {
	cin >> x >> y >> mx >> my;
	q.push(make_pair(y + 1 - my, mx));
	for (int i = 1; i <= y; i++) scanf("%s", s[i] + 1);
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= y; i++)
		for (int j = 1; j <= x; j++)
			if (s[i][j] == '*') v[i][j] = 1;
	v[y+1-my][mx] = 1;
	memset(d, 0, sizeof(d));
	while (q.size()) {
		pair<int, int> now = q.front();
		q.pop();
		for (int i = 0; i < 8; i++) {
			pair<int, int> nxt;
			nxt.first = now.first + dx[i];
			nxt.second = now.second + dy[i];
			if (nxt.first < 1 || nxt.first > y || nxt.second < 1 || nxt.second > x) continue;
			if (v[nxt.first][nxt.second]) continue;
			v[nxt.first][nxt.second] = 1;
			d[nxt.first][nxt.second] = d[now.first][now.second] + 1;
			q.push(nxt);
		}
		if (pd()) {
			cout << d[now.first][now.second] + 1 << endl;
			return 0;
		}
	}
	return 0;
}
