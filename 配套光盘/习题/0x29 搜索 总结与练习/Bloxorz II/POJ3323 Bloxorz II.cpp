//Author:XuHt
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 206, INF = 0x7fffffff;
char c[2];
int x, y, d[N][N][3], ans;
bool v[N][N][3];
int nx[3][4] = {{-2,1,0,0},{-1,1,0,0},{-1,2,0,0}};
int ny[3][4] = {{0,0,-2,1},{0,0,-1,2},{0,0,-1,1}};
int nz[3][4] = {{2,2,1,1},{1,1,0,0},{0,0,2,2}};
struct P {
	int x, y, z;
} now, nxt;
queue <P> q;

bool pd(int x, int y) {
	return x <= 200 && x > 0 && y <= 200 && y > 0;
}

int calc(int x, int y) {
	int num = 0;
	if (!pd(x, y)) {
		if (x > 200) {
			int k = (x - 200) / 3 + 2;
			num += k * 2;
			x -= k * 3;
		}
		if (y > 200) {
			int k = (y - 200) / 3 + 2;
			num += k * 2;
			y -= k * 3;
		}
	}
	return num + d[x][y][0];
}

int main() {
	memset(v, 0, sizeof(v));
	now.x = now.y = 100;
	now.z = 0;
	v[100][100][0] = 1;
	q.push(now);
	while (q.size()) {
		now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			nxt.x = now.x + nx[now.z][i];
			nxt.y = now.y + ny[now.z][i];
			nxt.z = nz[now.z][i];
			if (!pd(nxt.x, nxt.y)) continue;
			if (v[nxt.x][nxt.y][nxt.z]) continue;
			q.push(nxt);
			v[nxt.x][nxt.y][nxt.z] = 1;
			d[nxt.x][nxt.y][nxt.z] = d[now.x][now.y][now.z] + 1;
		}
	}
	while (scanf("%s", c) != EOF) {
		scanf("%d %d", &x, &y);
		x += 100;
		y += 100;
		ans = (c[0] == 'U' ? calc(x, y) : INF);
		if (c[0] == 'H')
			for (int i = -2; i <= 2; i++) {
				ans = min(ans, calc(x + i, y - 1) + abs(i) + 1);
				ans = min(ans, calc(x + i, y + 2) + abs(i) + 1);
			}
		else if(c[0] == 'V')
			for (int i = -2; i <= 2; i++) {
				ans = min(ans, calc(x - 1, y + i) + abs(i) + 1);
				ans = min(ans, calc(x + 2, y + i) + abs(i) + 1);
			}
		cout << ans << endl;
	}
	return 0;
}
