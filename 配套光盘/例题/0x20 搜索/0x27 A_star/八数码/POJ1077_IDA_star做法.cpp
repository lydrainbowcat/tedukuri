//Author:WFZWF
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
string st, ed;
int depth, ans[50];
int hfunc(string st) {
	int ans = 0;
	for (register int i = 0; i < st.size(); ++i) {
		if (st[i] == '0') continue;
		int j = ed.find(st[i]), r = i / 3, c = i % 3;
		int x = j / 3, y = j % 3;
		ans += abs(r - x) + abs(c - y);
	}
	return ans;
}
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1}, step[4] = {'u', 'l', 'd', 'r'};
bool dfs(int now, int pre) {
	int cnt = hfunc(st);
	if (!cnt) return 1;
	if (now + cnt > depth) return 0;
	int pos = st.find('0'), x = pos / 3, y = pos % 3;
	for (register int i = 0; i < 4; ++i) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || nx > 2 || ny < 0 || ny > 2 || nx * 3 + ny == pre) continue;
		swap(st[pos], st[nx * 3 + ny]);
		ans[now + 1] = step[i];
		if (dfs(now + 1, pos)) return 1;
		swap(st[pos], st[nx * 3 + ny]);
	}
	return 0;
}
int main() {
	for (register int i = 1; i <= 9; ++i) {
		char s[2];
		scanf("%s", s);
		st += s[0] == 'x' ? '0' : s[0];
	}
	int cnt = 0;
	for (register int i = 0; i < st.size(); ++i)
		if (st[i] != '0')
			for (register int j = 0; j < i; ++j)
				if (st[j] != '0') cnt += st[i] > st[j];
	if (cnt & 1) {
		puts("unsolvable");
		return 0;
	}
	ed = "123456780";
	for (depth = hfunc(st); !dfs(0, -1); ++depth);
	for (register int i = 1; i <= depth; ++i)
		putchar(ans[i]);
}
