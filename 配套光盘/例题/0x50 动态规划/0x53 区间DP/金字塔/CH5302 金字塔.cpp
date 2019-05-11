//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 306, P = 1000000000;
char s[N];
ll f[N][N];

ll dfs(int l, int r) {
	if (l > r) return 0;
	if (l == r) return 1;
	if (f[l][r] != -1) return f[l][r];
	if (s[l] != s[r]) return 0;
	f[l][r] = 0;
	for (int k = l + 2; k <= r; k++)
		(f[l][r] += dfs(l + 1, k - 1) * dfs(k, r)) %= P;
	return f[l][r];
}

int main() {
	scanf("%s", s + 1);
	memset(f, -1, sizeof(f));
	cout << dfs(1, strlen(s + 1)) << endl;
	return 0;
}
