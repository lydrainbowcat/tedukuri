#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int p[11] = { 1,3,9,27,81,243,729,2187,6561,19683,59049 };
int n, m;
int f[105][59050];
char a[105][12];
int v[15];
/* 2表示放置了炮兵，2下面必须是1，1下边必须是0，同一行两个2间隔不小于3
    0
    0
0 0 2 0 0
    1
    0
*/
// 标记第row行可以填的数字的情况
// 0表示只能填0，1表示只能填1，2表示可以填2或0
void mark(int row, int last) {
	for (int i = 1; i <= m; i++, last /= 3) {
		if (last % 3 == 2) v[i] = 1; // 2的下面只能填1
		else if (last % 3 == 1) v[i] = 0; // 1的下面只能填0
		else if (a[row][i] == 'H') v[i] = 0; // 山地不能填2
		else v[i] = 2; // 既可以填2，也可以填0
	}
}

// 已知第row行的状态为last，尝试在第row+1行放炮兵
// 第row+1行搜到了第col列，状态压缩为now，放了cnt个炮兵
// 状态压缩时，第1~m列分别对应三进制数now的第0~m-1位
void dfs(int row, int col, int last, int now, int cnt) {
	if (col > m) { // 填完了当前行，DP转移
		f[row + 1][now] = max(f[row + 1][now], f[row][last] + cnt);
		return;
	}
	if (v[col] == 2) { // 填2
		int v1 = v[col + 1], v2 = v[col + 2];
		if (v[col + 1] == 2) v[col + 1] = 0; // col+1列不能填2
		if (v[col + 2] == 2) v[col + 2] = 0; // col+2列不能填2
		dfs(row, col + 1, last, now + 2 * p[col - 1], cnt + 1);
		v[col + 1] = v1, v[col + 2] = v2; // 还原现场
	}
	if (v[col] == 1)
		dfs(row, col + 1, last, now + p[col - 1], cnt); // 填1
	if (v[col] == 2 || v[col] == 0)
		dfs(row, col + 1, last, now, cnt); // 填0
}


int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	memset(f, -1, sizeof(f));
	f[0][0] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < p[10]; j++) {
			if (f[i][j] < 0) continue;
			mark(i + 1, j);
			dfs(i, 1, j, 0, 0);
		}
	int ans = 0;
	for (int j = 0; j < p[10]; j++) ans = max(ans, f[n][j]);
	cout << ans << endl;
}
