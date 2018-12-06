//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 370;
int n, a[N];
bool v[N][10][8][8][8][8];
int dx[10] = {0,0,1,2,-1,-2,0,0,0,0};
int dy[10] = {0,0,0,0,0,0,1,2,-1,-2};
struct P {
	int d[5];
} st;

int get(int x, int y) {
	return 1 << (16 - ((x - 1) * 4 + y));
}

bool pd(int day, int x, int y, P now) {
	for (int i = 1; i < 5; i++) if (now.d[i] == 7) return 0;
	int flag = get(x, y) | get(x, y + 1) | get(x + 1, y) | get(x + 1, y + 1);
	if (flag & a[day]) return 0;
	if (v[day][(x-1)*3+y][now.d[1]][now.d[2]][now.d[3]][now.d[4]]) return 0;
	return v[day][(x-1)*3+y][now.d[1]][now.d[2]][now.d[3]][now.d[4]] = 1;
}

bool dfs(int day, int x, int y, P now) {
	if (day == n + 1) return 1;
	if (!pd(day, x, y, now)) return 0;
	for (int i = 1; i < 10; i++) {
		P nxt = now;
		for (int j = 1; j < 5; j++) ++nxt.d[j];
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 1 || nx > 3 || ny < 1 || ny > 3) continue;
		if (nx == 1) {
			if (ny == 1) nxt.d[1] = 0;
			else if (ny == 3) nxt.d[2] = 0;
		} else if (nx == 3) {
			if (ny == 1) nxt.d[3] = 0;
			else if (ny == 3) nxt.d[4] = 0;
		}
		if (dfs(day + 1, nx, ny, nxt)) return 1;
	}
	return 0;
}

int main() {
	while (cin >> n && n) {
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= 16; j++) {
				int w;
				cin >> w;
				(a[i] <<= 1) |= w;
			}
		memset(v, 0, sizeof(v));
		for (int i = 1; i < 5; i++) st.d[i] = 1;
		puts(dfs(1, 2, 2, st) ? "1" : "0");
	}
	return 0;
}
