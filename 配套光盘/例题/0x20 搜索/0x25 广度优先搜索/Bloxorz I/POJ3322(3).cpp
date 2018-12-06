//Author:XuHt
#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
struct P {
	int x, y, z;
} st, ed;
const int N = 506;
char s[N][N];
int n, m, d[N][N][3];
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int nx[3][4] = {{0,0,-2,1},{0,0,-1,1},{0,0,-1,2}};
int ny[3][4] = {{-2,1,0,0},{-1,2,0,0},{-1,1,0,0}};
int nz[3][4] = {{1,1,2,2},{0,0,1,1},{2,2,0,0}};
queue<P> q;

bool pd(int x, int y) {
	return x >= 1 && y >= 1 && x <= n && y <= m;
}

bool pd(P p) {
	if (!pd(p.x, p.y)) return 0;
	if (s[p.x][p.y] == '#') return 0;
	if (p.z == 0 && s[p.x][p.y] != '.') return 0;
	if (p.z == 1 && s[p.x][p.y+1] == '#') return 0;
	if (p.z == 2 && s[p.x+1][p.y] == '#') return 0;
	return 1;
}

int bfs() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 0; k < 3; k++)
				d[i][j][k] = -1;
	queue<P> empty;
	swap(q, empty);
	d[st.x][st.y][st.z] = 0;
	q.push(st);
	while (q.size()) {
		P now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			P p;
			p.x = now.x + nx[now.z][i];
			p.y = now.y + ny[now.z][i];
			p.z = nz[now.z][i];
			if (!pd(p)) continue;
			if (d[p.x][p.y][p.z] == -1) {
				d[p.x][p.y][p.z] = d[now.x][now.y][now.z] + 1;
				q.push(p);
				if (p.x == ed.x && p.y == ed.y && p.z == ed.z)
					return d[p.x][p.y][p.z];
			}
		}
	}
	return -1;
}

int main() {
	while (cin >> n >> m && n) {
		for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (s[i][j] == 'O') {
					ed.x = i;
					ed.y = j;
					ed.z = 0;
					s[i][j] = '.';
				} else if (s[i][j] == 'X') {
					for (int k = 0; k < 4; k++) {
						int x = i + dx[k], y = j + dy[k];
						if (pd(x, y) && s[x][y] == 'X') {
							st.x = min(i, x);
							st.y = min(j, y);
							st.z = k < 2 ? 1 : 2;
							s[i][j] = s[x][y] = '.';
							break;
						}
					}
					if (s[i][j] == 'X') {
						st.x = i;
						st.y = j;
						st.z = 0;
					}
				}
		int ans = bfs();
		if (ans == -1) puts("Impossible");
		else cout << ans << endl;
	}
	return 0;
}
