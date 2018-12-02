//Author:XuHt
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const double eps = 0.00000001;
const int N = 10006;
char s[N][100], p[N];
int r0, c0, Next[N];

int get() {
	int len = strlen(p), i = 0, j = Next[0] = -1;
	while (i < len) {
		while (j != -1 && p[i] != p[j]) j = Next[j];
		Next[++i] = ++j;
	}
	return len - Next[len];
}

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	cin >> r0 >> c0;
	for (int i = 0; i < r0; i++) scanf("%s", s[i]);
	ll r = 1, c = 1;
	for (int i = 0; i < r0; i++) {
		for (int j = 0; j < c0; j++)
			p[j] = s[i][j];
		p[c0] = '\0';
		int k = get();
		r = k / gcd(r, k) * r;
		if (r >= c0) {
			r = c0;
			break;
		}
	}
	for (int i = 0; i < c0; i++) {
		for (int j = 0; j < r0; j++)
			p[j] = s[j][i];
		p[r0] = '\0';
		int k = get();
		c = k / gcd(c, k) * c;
		if (c >= r0) {
			c = r0;
			break;
		}
	}
	cout << c * r << endl;
	return 0;
}
