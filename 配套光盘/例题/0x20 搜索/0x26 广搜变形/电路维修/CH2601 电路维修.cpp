//Author:XuHt
#include <deque>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 506;
int r, c, d[N][N];
bool v[N][N];
char s[N][N];
vector<pair<pair<int, int>, int> > p[N][N];
deque<pair<int, int> > q;

void add(int x1, int y1, int x2, int y2, int z) {
	p[x1][y1].push_back(make_pair(make_pair(x2, y2), z));
}

void dlwx() {
	cin >> r >> c;
	for (int i = 1; i <= r; i++) cin >> (s[i] + 1);
	if ((r & 1) != (c & 1)) cout << "NO SOLUTION" << endl;
	for (int i = 0; i <= r; i++)
		for (int j = 0; j <= c; j++)
			p[i][j].clear();
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
			if (s[i][j] == '/') {
				add(i - 1, j - 1, i, j, 1);
				add(i, j, i - 1, j - 1, 1);
				add(i, j - 1, i - 1, j, 0);
				add(i - 1, j, i, j - 1, 0);
			} else {
				add(i - 1, j - 1, i, j, 0);
				add(i, j, i - 1, j - 1, 0);
				add(i, j - 1, i - 1, j, 1);
				add(i - 1, j, i, j - 1, 1);
			}
	memset(d, 0x3f, sizeof(d));
	d[0][0] = 0;
	memset(v, 0, sizeof(v));
	q.clear();
	q.push_back(make_pair(0, 0));
	while (q.size()) {
		int x = q.front().first, y = q.front().second;
		q.pop_front();
		v[x][y] = 1;
		if (x == r && y == c) {
			cout << d[r][c] << endl;
			return;
		}
		for (unsigned int i = 0; i < p[x][y].size(); i++) {
			int nx = p[x][y][i].first.first;
			int ny = p[x][y][i].first.second;
			int nz = p[x][y][i].second;
			if (v[nx][ny]) continue;
			if (nz) {
				if (d[nx][ny] > d[x][y] + 1) {
					d[nx][ny] = d[x][y] + 1;
					q.push_back(make_pair(nx, ny));
				}
			} else {
				if (d[nx][ny] > d[x][y]) {
					q.push_front(make_pair(nx, ny));
					d[nx][ny] = d[x][y];
				}
			}
		}
	}
}

int main() {
	int t;
	cin >> t;
	while (t--) dlwx();
	return 0;
}
