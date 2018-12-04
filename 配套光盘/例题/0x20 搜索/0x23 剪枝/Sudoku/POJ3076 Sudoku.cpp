//Author:XuHt
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
char s[16][16];
int cnt[1<<16], f[1<<16], num[16][16], n = 0;
vector<int> e[1<<16];

void work(int i, int j, int k) {
	for (int t = 0; t < 16; t++) {
		num[i][t] &= ~(1 << k);
		num[t][j] &= ~(1 << k);
	}
	int x = i / 4 * 4, y = j / 4 * 4;
	for (int ti = 0; ti < 4; ti++)
		for (int tj = 0; tj < 4; tj++)
			num[x+ti][y+tj] &= ~(1 << k);
}

bool dfs(int ans) {
	if (!ans) return 1;
	int pre[16][16];
	memcpy(pre, num, sizeof(pre));
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			if (s[i][j] == '-') {
				if (!num[i][j]) return 0;
				if (cnt[num[i][j]] == 1) {
					s[i][j] = f[num[i][j]] + 'A';
					work(i, j, f[num[i][j]]);
					if (dfs(ans - 1)) return 1;
					s[i][j] = '-';
					memcpy(num, pre, sizeof(num));
					return 0;
				}
			}
	for (int i = 0; i < 16; i++) {
		int w[16], o = 0;
		memset(w, 0, sizeof(w));
		for (int j = 0; j < 16; j++)
			if (s[i][j] == '-') {
				o |= num[i][j];
				for (unsigned int k = 0; k < e[num[i][j]].size(); k++)
					++w[e[num[i][j]][k]];
			} else {
				o |= (1 << (s[i][j] - 'A'));
				w[f[1<<(s[i][j]-'A')]] = -1;
			}
		if (o != (1 << 16) - 1) return 0;
		for (int k = 0; k < 16; k++)
			if (w[k] == 1)
				for (int j = 0; j < 16; j++)
					if (s[i][j] == '-' && ((num[i][j] >> k) & 1)) {
						s[i][j] = k + 'A';
						work(i, j, k);
						if (dfs(ans - 1)) return 1;
						s[i][j] = '-';
						memcpy(num, pre, sizeof(num));
						return 0;
					}
	}
	for (int j = 0; j < 16; j++) {
		int w[16], o = 0;
		memset(w, 0, sizeof(w));
		for (int i = 0; i < 16; i++)
			if (s[i][j] == '-') {
				o |= num[i][j];
				for (unsigned int k = 0; k < e[num[i][j]].size(); k++)
					++w[e[num[i][j]][k]];
			} else {
				o |= (1 << (s[i][j] - 'A'));
				w[f[1<<(s[i][j]-'A')]] = -1;
			}
		if (o != (1 << 16) - 1) return 0;
		for (int k = 0; k < 16; k++)
			if (w[k] == 1)
				for (int i = 0; i < 16; i++)
					if (s[i][j] == '-' && ((num[i][j] >> k) & 1)) {
						s[i][j] = k + 'A';
						work(i, j, k);
						if (dfs(ans - 1)) return 1;
						s[i][j] = '-';
						memcpy(num, pre, sizeof(num));
						return 0;
					}
	}
	for (int i = 0; i < 16; i += 4)
		for (int j = 0; j < 16; j += 4) {
			int w[16], o = 0;
			memset(w, 0, sizeof(w));
			for (int p = 0; p < 4; p++)
				for (int q = 0; q < 4; q++)
					if (s[i+p][j+q] == '-') {
						o |= num[i+p][j+q];
						for (unsigned int k = 0; k < e[num[i+p][j+q]].size(); k++)
							++w[e[num[i+p][j+q]][k]];
					} else {
						o |= (1 << (s[i+p][j+q] - 'A'));
						w[f[1<<(s[i+p][j+q]-'A')]] = -1;
					}
			if (o != (1 << 16) - 1) return 0;
			for (int k = 0; k < 16; k++)
				if (w[k] == 1)
					for (int p = 0; p < 4; p++)
						for (int q = 0; q < 4; q++)
							if (s[i+p][j+q] == '-' && ((num[i+p][j+q] >> k) & 1)) {
								s[i+p][j+q] = k + 'A';
								work(i + p, j + q, k);
								if (dfs(ans - 1)) return 1;
								s[i+p][j+q] = '-';
								memcpy(num, pre, sizeof(num));
								return 0;
							}
		}
	int k = 17, tx, ty;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			if (s[i][j] == '-' && cnt[num[i][j]] < k) {
				k = cnt[num[i][j]];
				tx = i;
				ty = j;
			}
	for (unsigned int i = 0; i < e[num[tx][ty]].size(); i++) {
		int tz = e[num[tx][ty]][i];
		work(tx, ty, tz);
		s[tx][ty] = tz + 'A';
		if (dfs(ans - 1)) return 1;
		s[tx][ty] = '-';
		memcpy(num, pre, sizeof(num));
	}
	return 0;
}

void Sudoku() {
	for (int i = 1; i < 16; i++) cin >> s[i];
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			num[i][j] = (1 << 16) - 1;
	int ans = 0;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			if (s[i][j] != '-') work(i, j, s[i][j] - 'A');
			else ++ans;
	dfs(ans);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) cout << s[i][j];
		cout << endl;
	}
	cout << endl;
}

int get_cnt(int i) {
	int k = i & -i;
	e[i].push_back(f[k]);
	for (unsigned int j = 0; j < e[i-k].size(); j++)
		e[i].push_back(e[i-k][j]);
	return cnt[i-k] + 1;
}

int main() {
	memset(f, 0, sizeof(f));
	for (int i = 0; i < 16; i++) f[1<<i] = i;
	cnt[0] = 0;
	for (int i = 1; i < (1 << 16); i++) cnt[i] = get_cnt(i);
	while (cin >> s[0]) Sudoku();
	return 0;
}
