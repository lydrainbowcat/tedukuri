//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#define ull unsigned long long
using namespace std;
const int R = 10006, C = 81, P = 13331;
int r, c, nxt[R];
char s[R][C];
ull H[R];

int work(int len) {
	int i = 0, j = -1;
	nxt[0] = -1;
	while (i < len)
		if (j == -1 || H[i] == H[j]) nxt[++i] = ++j;
		else j = nxt[j];
	return len - nxt[len];
}

int main() {
	cin >> r >> c;
	for (int i = 0; i < r; i++) scanf("%s", s[i]);
	memset(H, 0, sizeof(H));
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			H[i] = H[i] * P + s[i][j];
	int ans = work(r);
	memset(H, 0, sizeof(H));
	for (int i = 0; i < c; i++)
		for (int j = 0; j < r; j++)
			H[i] = H[i] * P + s[j][i];
	ans *= work(c);
	cout << ans << endl;
	return 0;
}
