#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct rec { int x, y, lie; };  // 状态
char s[510][510];  // 地图
rec st, ed;  // 起始状态和目标状态
int n, m, d[510][510][3];  // 最少步数记录数组
queue<rec> q;  // 队列
bool valid(int x, int y) { return x>=1 && y>=1 && x<=n && y<=m; }
// 方向数组（方向0~3依次代表左右上下）
const int dx[4] = { 0,0,-1,1 }, dy[4] = { -1,1,0,0 };

void parse_st_ed() {  // 处理起点和终点
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] == 'O') {
				ed.x = i, ed.y = j, ed.lie = 0, s[i][j] = '.';
			}
			else if (s[i][j] == 'X') {
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k], y = j + dy[k];
					if (valid(x, y) && s[x][y] == 'X') {
						st.x = min(i,x), st.y = min(j,y), st.lie = k<2?1:2;
						s[i][j] = s[x][y] = '.';
						break;
					}
				}
				if (s[i][j] == 'X') {
					st.x = i, st.y = j, st.lie = 0;
				}
			}
}

bool valid(rec next) {  // 滚动是否合法
	if (!valid(next.x, next.y)) return 0;
	if (s[next.x][next.y] == '#') return 0;
	if (next.lie == 0 && s[next.x][next.y] != '.') return 0;
	if (next.lie == 1 && s[next.x][next.y + 1] == '#') return 0;
	if (next.lie == 2 && s[next.x + 1][next.y] == '#') return 0;
	return 1;
}

// next_x[i][j]表示在lie=i时朝方向j滚动后x的变化情况
const int next_x[3][4] = { { 0,0,-2,1 },{ 0,0,-1,1 },{ 0,0,-1,2 } };
// next_y[i][j]表示在lie=i时朝方向j滚动后y的变化情况
const int next_y[3][4] = { { -2,1,0,0 },{ -1,2,0,0 },{ -1,1,0,0 } };
// next_lie[i][j]表示在lie=i时朝方向j滚动后lie的新值
const int next_lie[3][4] = { { 1,1,2,2 },{ 0,0,1,1 },{ 2,2,0,0 } };

int bfs() {  // 广搜
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 0; k < 3; k++) d[i][j][k] = -1;
	while (q.size()) q.pop();
	d[st.x][st.y][st.lie] = 0;
	q.push(st);
	while (q.size()) {
		rec now = q.front(); q.pop();  // 取出队头
		for (int i = 0; i < 4; i++) {  // 向4个方向滚动
			rec next;
			next.x = now.x + next_x[now.lie][i];
			next.y = now.y + next_y[now.lie][i];
			next.lie = next_lie[now.lie][i];
			if (!valid(next)) continue;
			if (d[next.x][next.y][next.lie] == -1) {  // 尚未访问过
				d[next.x][next.y][next.lie] = d[now.x][now.y][now.lie]+1;
				q.push(next);
				if (next.x == ed.x && next.y == ed.y && next.lie == ed.lie)
					return d[next.x][next.y][next.lie];  // 到达目标
			}
		}
	}
	return -1;  // 无解
}

int main() {
	while (cin >> n >> m && n) {
		for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
		parse_st_ed();
		int ans = bfs();
		if (ans == -1) puts("Impossible"); else cout << ans << endl;
	}
}