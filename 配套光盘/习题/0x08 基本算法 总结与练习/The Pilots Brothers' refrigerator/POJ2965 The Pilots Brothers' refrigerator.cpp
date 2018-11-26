//Author:XuHt
#include <cstring>
#include <iostream>
using namespace std;
char s[4][4];
bool a[4][4], c[4][4];
int p[37];

int num(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x -= x & -x;
	}
	return ans;
}

void dj(int x, int y) {
	for (int i = 0; i < 4; i++) {
		c[x][i] ^= 1;
		c[i][y] ^= 1;
	}
	c[x][y] ^= 1;
}

bool pd(int x) {
	memcpy(c, a, sizeof(c));
	while (x) {
		int k = (x & -x) % 37;
		dj(p[k] / 4, p[k] % 4);
		x -= x & -x;
	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (!c[i][j]) return 0;
	return 1;
}

int main() {
	for (int i = 0; i < 4; i++) cin >> s[i];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			a[i][j] = (s[i][j] == '-');
	int ans = 17, x, t = 1;
	for (int i = 0; i < 16; i++) {
		p[t%37] = i;
		t *= 2;
	}
	for (int i = 0; i < (1 << 16); i++) {
		int n = num(i);
		if (n < ans && pd(i)) {
			ans = n;
			x = i;
		}
	}
	cout << ans << endl;
	while (x) {
		int w = (x & -x) % 37;
		cout << p[w] / 4 + 1 << " " << p[w] % 4 + 1 << endl;
		x -= (x & -x);
	}
	return 0;
}
