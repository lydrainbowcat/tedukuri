//Author:XuHt
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
char ed[5][5] = {
	{'1','1','1','1','1'},
	{'0','1','1','1','1'},
	{'0','0','*','1','1'},
	{'0','0','0','0','1'},
	{'0','0','0','0','0'}
}, a[5][5];
int dx[8] = {-2,-2,-1,-1,1,1,2,2};
int dy[8] = {-1,1,-2,2,-2,2,-1,1};
int dep, x, y;

int gj() {
	int ans = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == '*') {
				x = i;
				y = j;
			}
			if (a[i][j] != ed[i][j]) ++ans;
		}
	return ans;
}

bool dfs(int now) {
	int cnt = gj(), nowx = x, nowy = y;
	if (now + cnt - 1 > dep) return 0;
	if (!cnt) return 1;
	for (int i = 0; i < 8; i++) {
		int nx = nowx + dx[i], ny = nowy + dy[i];
		if (nx < 0 || nx > 4 || ny < 0 || ny > 4) continue;
		swap(a[nowx][nowy], a[nx][ny]);
		if (dfs(now + 1)) return 1;
		swap(a[nowx][nowy], a[nx][ny]);
	}
	return 0;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		for (int i = 0; i < 5; i++) cin >> a[i];
		dep = 0;
		while (dep <= 15 && !dfs(0)) ++dep;
		if (dep == 16) puts("-1");
		else cout << dep << endl;
	}
	return 0;
}
