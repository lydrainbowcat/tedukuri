//Author:XuHt
//POJ3074
#include <cstring>
#include <iostream>
using namespace std;
char s[81];
int cnt[1<<9], f[1<<9];
int x[9], y[9], z[9], X[81], Y[81];
int gx, gy, gz;

inline void get(int i) {
	gx = X[i];
	gy = Y[i];
	gz = gx / 3 * 3 + gy / 3;
}

void work(int i, int k) {
	get(i);
	x[gx] ^= (1 << k);
	y[gy] ^= (1 << k);
	z[gz] ^= (1 << k);
}

bool dfs(int ans) {
	if (!ans) return 1;
	int k = 10, t;
	for (int i = 0; i < 81; i++)
		if (s[i] == '.') {
			get(i);
			int w = x[gx] & y[gy] & z[gz];
			if (cnt[w] < k) {
				k = cnt[w];
				t = i;
			}
		}
	get(t);
	int w = x[gx] & y[gy] & z[gz];
	while (w) {
		int now = f[w&-w];
		s[t] = now + '1';
		work(t, now);
		if (dfs(ans - 1)) return 1;
		work(t, now);
		s[t] = '.';
		w -= w & -w;
	}
	return 0;
}

void Sudoku() {
	for (int i = 0; i < 9; i++) x[i] = y[i] = z[i] = (1 << 9) - 1;
	int ans = 0;
	for (int i = 0; i < 81; i++)
		if (s[i] != '.') work(i, s[i] - '1');
		else ++ans;
	if (dfs(ans)) for (int i = 0; i < 81; i++) cout << s[i];
	cout << endl;
}

int get_cnt(int i) {
	int ans = 0;
	while (i) {
		++ans;
		i -= (i & -i);
	}
	return ans;
}

int main() {
	for (int i = 0; i < (1 << 9); i++) cnt[i] = get_cnt(i);
	for (int i = 0; i < 9; i++) f[1<<i] = i;
	for (int i = 0; i < 81; i++) {
		X[i] = i / 9;
		Y[i] = i % 9;
	}
	while (cin >> s && s[0] != 'e') Sudoku();
	return 0;
}
