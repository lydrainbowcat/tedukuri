//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
ll f[70], d[70][70], e[70][70][70];
char b[20][20], s[100];
int n, m, t, act, p, a[20][20], c[20][20];

inline int num(int i, int j) {
	return (i - 1) * m + j;
}

void mulself(ll a[70][70], ll b[70][70]) {
	ll w[70][70];
	memset(w, 0, sizeof(w));
	for (int i = 1; i <= p; i++)
		for (int k = 1; k <= p; k++)
			if (a[i][k])
				for (int j = 1; j <= p; j++)
					w[i][j] += a[i][k] * b[k][j];
	memcpy(a, w, sizeof(w));
}

void mul(ll a[70], ll b[70][70]) {
	ll w[70];
	memset(w, 0, sizeof(w));
	for (int i = 1; i <= p; i++)
		for (int j = 1; j <= p; j++)
			w[i] += a[j] * b[j][i];
	memcpy(f, w, sizeof(w));
}

int main() {
	cin >> n >> m >> t >> act;
	for (int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= m; j++) a[i][j] = s[j] - '0' + 1;
	}
	for (int i = 1; i <= act; i++) scanf("%s", b[i]);
	p = n * m + 1;
	for (int k = 1; k <= 60; k++) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				int x = a[i][j], y = c[i][j];
				if (b[x][y] >= '0' && b[x][y] <= '9') {
					e[k][p][num(i,j)] = b[x][y] - '0';
					e[k][num(i,j)][num(i,j)] = 1;
				} else if (b[x][y] == 'N' && i > 1) e[k][num(i,j)][num(i-1,j)] = 1;
				else if (b[x][y] == 'W' && j > 1) e[k][num(i,j)][num(i,j-1)] = 1;
				else if (b[x][y] == 'S' && i < n) e[k][num(i,j)][num(i+1,j)] = 1;
				else if (b[x][y] == 'E' && j < m) e[k][num(i,j)][num(i,j+1)] = 1;
				c[i][j] = (y + 1) % strlen(b[x]);
			}
		e[k][p][p] = 1;
	}
	memcpy(d, e[1], sizeof(e[1]));
	for (int k = 2; k <= 60; k++) mulself(d, e[k]);
	ll ans = 0;
	f[p] = 1;
	int w = t / 60;
	while (w) {
		if (w & 1) mul(f, d);
		mulself(d, d);
		w >>= 1;
	}
	w = t % 60;
	for (int i = 1; i <= w; i++) mul(f, e[i]);
	for (int i = 1; i < p; i++) ans = max(ans, f[i]);
	cout << ans << endl;
	return 0;
}
