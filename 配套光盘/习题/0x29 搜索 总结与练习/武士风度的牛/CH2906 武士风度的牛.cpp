//Author:XuHt
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 156;
char s[N][N];
bool v[N][N];
int dx[8] = {-2,-1,1,2,2,1,-1,-2};
int dy[8] = {1,2,2,1,-1,-2,-2,-1};
struct P {
	int x, y, ans;
} st, ed;
queue<P> q;
int main() {
	memset(v, 0, sizeof(v));
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> (s[i] + 1);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (s[i][j] == 'K') {
				st.x = i;
				st.y = j;
				st.ans = 0;
				q.push(st);
				v[i][j] = 1;
			} else if (s[i][j] == 'H') {
				ed.x = i;
				ed.y = j;
			} else if (s[i][j] == '*') v[i][j] = 1;
	while (q.size()) {
		P p = q.front();
		if (p.x == ed.x && p.y == ed.y) {
			cout << p.ans << endl;
			return 0;
		}
		q.pop();
		for (int i = 0; i < 8; i++) {
			int nx = p.x + dx[i], ny = p.y + dy[i];
			if (nx < 0 || ny < 0 || nx > m || ny > n) continue;
			if (v[nx][ny]) continue;
			P np;
			np.x = nx;
			np.y = ny;
			np.ans = p.ans + 1;
			q.push(np);
			v[nx][ny] = 1;
		}
	}
	return 0;
}
