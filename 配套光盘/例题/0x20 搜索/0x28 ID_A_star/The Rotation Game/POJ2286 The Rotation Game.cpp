//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int a[9][9], dep;
vector<char> ans;

void work(int k) {
	if (k == 1) {
		for (int i = 1; i < 8; i++) a[i-1][3] = a[i][3];
		a[7][3] = a[0][3];
	} else if (k == 2) {
		for (int i = 1; i < 8; i++) a[i-1][5] = a[i][5];
		a[7][5] = a[0][5];
	} else if (k == 3) {
		for (int i = 7; i; i--) a[3][i+1] = a[3][i];
		a[3][1] = a[3][8];
	} else if (k == 4) {
		for (int i = 7; i; i--) a[5][i+1] = a[5][i];
		a[5][1] = a[5][8];
	} else if (k == 5) {
		for (int i = 7; i; i--) a[i+1][5] = a[i][5];
		a[1][5] = a[8][5];
	} else if (k == 6) {
		for (int i = 7; i; i--) a[i+1][3] = a[i][3];
		a[1][3] = a[8][3];
	} else if (k == 7) {
		for (int i = 1; i < 8; i++) a[5][i-1] = a[5][i];
		a[5][7] = a[5][0];
	} else {
		for (int i = 1; i < 8; i++) a[3][i-1] = a[3][i];
		a[3][7] = a[3][0];
	}
}

int gj() {
	int num[4];
	num[1] = num[2] = num[3] = 0;
	for (int i = 3; i < 6; i++)
		for (int j = 3; j < 6; j++) {
			if (i == 4 && j == 4) continue;
			++num[a[i][j]];
		}
	return 8 - max(num[1], max(num[2], num[3]));
}

bool dfs(int now) {
	int cnt = gj();
	if (!cnt) return 1;
	if (now + cnt > dep) return 0;
	int b[9][9];
	memcpy(b, a, sizeof(b));
	for (int i = 1; i < 9; i++) {
		if (ans.size()) {
			int k = ans.back();
			if (k - 'A' + 1 == 1 && i == 6) continue;
			if (k - 'A' + 1 == 2 && i == 5) continue;
			if (k - 'A' + 1 == 3 && i == 8) continue;
			if (k - 'A' + 1 == 4 && i == 7) continue;
			if (k - 'A' + 1 == 5 && i == 2) continue;
			if (k - 'A' + 1 == 6 && i == 1) continue;
			if (k - 'A' + 1 == 7 && i == 4) continue;
			if (k - 'A' + 1 == 8 && i == 3) continue;
		}
		ans.push_back(i + 'A' - 1);
		work(i);
		if (dfs(now + 1)) return 1;
		ans.pop_back();
		memcpy(a, b, sizeof(a));
	}
	return 0;
}

void The_Rotation_Game() {
	cin >> a[1][5] >> a[2][3] >> a[2][5];
	for (int i = 1; i < 8; i++) cin >> a[3][i];
	cin >> a[4][3] >> a[4][5];
	for (int i = 1; i < 8; i++) cin >> a[5][i];
	cin >> a[6][3] >> a[6][5] >> a[7][3] >> a[7][5];
	ans.clear();
	dep = 0;
	while (!dfs(0)) ++dep;
	if (!dep) puts("No moves needed");
	else {
		for (unsigned int i = 0; i < ans.size(); i++)
			putchar(ans[i]);
		puts("");
	}
	cout << a[3][3] << endl;
}

int main() {
	while (cin >> a[1][3] && a[1][3]) The_Rotation_Game();
	return 0;
}
