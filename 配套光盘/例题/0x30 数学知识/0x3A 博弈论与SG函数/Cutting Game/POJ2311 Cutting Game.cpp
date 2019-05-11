//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 206;
int n, m, sg[N][N];

int SG(int x, int y) {
	bool f[N];
	memset(f, 0, sizeof(f));
	if (sg[x][y] != -1) return sg[x][y];
	for (int i = 2; i <= x - i; i++) f[SG(i,y)^SG(x-i,y)] = 1;
	for (int i = 2; i <= y - i; i++) f[SG(x,i)^SG(x,y-i)] = 1;
	int t = 0;
	while (f[t]) ++t;
	return sg[x][y] = t;
}

int main() {
	memset(sg, -1, sizeof(sg));
	sg[2][2] = sg[2][3] = sg[3][2] = 0;
	while (cin >> n >> m) puts(SG(n, m) ? "WIN" : "LOSE");
	return 0;
}
