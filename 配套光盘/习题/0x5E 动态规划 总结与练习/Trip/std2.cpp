//Author:XuHt
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106, M = 1006, X = 26;
int f[N][N], fa[N][X], fb[N][X], t = 0, z = 0;
string a, b, s[M];

void dp(int x, int y, string w, int l) {
	if ((int)w.size() == z) {
		s[++t] = w;
		return;
	}
	if (x < 0 || y < 0) return;
	if (a[x] == b[y]) {
		dp(x - 1, y - 1, a[x] + w, l - 1);
		return;
	}
	for (int i = 0; i < X; i++)
		if (f[fa[x+1][i]][fb[y+1][i]] == l)
			dp(fa[x+1][i] - 1, fb[y+1][i] - 1, w, l);
}

int main() {
	cin >> a >> b;
	for (unsigned int i = 0; i < a.size(); i++)
		for (unsigned int j = 0; j < b.size(); j++) {
			if (a[i] == b[j]) f[i+1][j+1] = f[i][j] + 1;
			else f[i+1][j+1] = max(f[i][j+1], f[i+1][j]);
			z = max(z, f[i+1][j+1]);
		}
	for (unsigned int i = 0; i < a.size(); i++)
		for (int j = 0; j < X; j++)
			if (a[i] != j + 'a') fa[i+1][j] = fa[i][j];
			else fa[i+1][j] = i + 1;
	for (unsigned int i = 0; i < b.size(); i++)
		for (int j = 0; j < X; j++)
			if (b[i] != j + 'a') fb[i+1][j] = fb[i][j];
			else fb[i+1][j] = i + 1;
	dp(a.size() - 1, b.size() - 1, "", z);
	sort(s + 1, s + t + 1);
	for (int i = 1; i <= t; i++) cout << s[i] << endl;
	return 0;
}
