//Author:XuHt
#include <queue>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 806;
char s[N][N];
bool v1[N][N], v2[N][N];
int n, m, bx, by, gx, gy, px, py, qx, qy, s1, s2;
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};

bool pd(int x, int y, int k) {
	if (x <= 0 || x > n || y <= 0 || y > m) return 0;
	if (abs(x - px) + abs(y - py) <= 2 * k) return 0;
	if (abs(x - qx) + abs(y - qy) <= 2 * k) return 0;
	if (s[x][y] == 'X') return 0;
	return 1;
}

int bfs() {
	queue<pair<int, int> > q1, q2;
	px = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] == 'M') {
				bx = i;
				by = j;
			} else if (s[i][j] == 'G') {
				gx = i;
				gy = j;
			} else if (s[i][j] == 'Z') {
				if (!px) {
					px = i;
					py = j;
				} else {
					qx = i;
					qy = j;
				}
			}
	int ans = 0;
	memset(v1, 0, sizeof(v1));
	memset(v2, 0, sizeof(v2));
	v1[bx][by] = 1;
	v2[gx][gy] = 1;
	q1.push(make_pair(bx, by));
	q2.push(make_pair(gx, gy));
	while (q1.size() || q2.size()) {
		ans++;
		s1 = q1.size();
		for (int i = 1; i <= s1; i++) {
			pair<int, int> now = q1.front();
			q1.pop();
			if (!pd(now.first,now.second,ans)) continue;
			for (int j = 0; j < 4; j++) {
				int nx = now.first + dx[j];
				int ny = now.second + dy[j];
				if (pd(nx,ny,ans) && !v1[nx][ny]) {
					v1[nx][ny] = 1;
					q1.push(make_pair(nx, ny));
				}
			}
		}
		s1 = q1.size();
		for (int i = 1; i <= s1; i++) {
			pair<int, int> now = q1.front();
			q1.pop();
			if (!pd(now.first,now.second,ans)) continue;
			for (int j = 0; j < 4; j++) {
				int nx = now.first + dx[j];
				int ny = now.second + dy[j];
				if (pd(nx,ny,ans) && !v1[nx][ny]) {
					v1[nx][ny] = 1;
					q1.push(make_pair(nx, ny));
				}
			}
		}
		s1 = q1.size();
		for (int i = 1; i <= s1; i++) {
			pair<int, int> now = q1.front();
			q1.pop();
			if (!pd(now.first,now.second,ans)) continue;
			for (int j = 0; j < 4; j++) {
				int nx = now.first + dx[j];
				int ny = now.second + dy[j];
				if (pd(nx,ny,ans) && !v1[nx][ny]) {
					v1[nx][ny] = 1;
					q1.push(make_pair(nx, ny));
				}
			}
		}
		s2 = q2.size();
		for (int i = 1; i <= s2; i++) {
			pair<int, int> now = q2.front();
			q2.pop();
			if (!pd(now.first,now.second,ans)) continue;
			for (int j = 0; j < 4; j++) {
				int nx = now.first + dx[j];
				int ny = now.second + dy[j];
				if (pd(nx,ny,ans) && !v2[nx][ny]) {
					if (v1[nx][ny]) return ans;
					v2[nx][ny] = 1;
					q2.push(make_pair(nx, ny));
				}
			}
		}
	}
	return -1;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			scanf("%s", s[i] + 1);
		cout << bfs() << endl;
	}
	return 0;
}
