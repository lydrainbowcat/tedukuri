//Author:XuHt
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 16, P = 10000007;
int n, m;
struct M {
	int n, m, a[N][N];
};

M mul(M x, M y) {
	M ans;
	ans.n = x.n;
	ans.m = y.m;
	memset(ans.a, 0, sizeof(ans.a));
	for (int i = 0; i <= ans.n; i++)
		for (int j = 0; j <= ans.m; j++)
			for (int k = 0; k <= x.m; k++)
				ans.a[i][j] = ((ll)x.a[i][k] * y.a[k][j] % P + ans.a[i][j]) % P;
	return ans;
}

M ksm(M x, int y) {
	M ans;
	ans.n = x.n;
	ans.m = x.m;
	memset(ans.a, 0, sizeof(ans.a));
	for (int i = 0; i <= x.n; i++) ans.a[i][i] = 1;
	while (y) {
		if (y & 1) ans = mul(ans, x);
		x = mul(x, x);
		y >>= 1;
	}
	return ans;
}

void Matrix() {
	M x, y;
	x.n = 0;
	y.n = y.m = x.m = n + 1;
	memset(x.a, 0, sizeof(x.a));
	memset(y.a, 0, sizeof(y.a));
	x.a[0][0] = 23;
	x.a[0][n+1] = 3;
	for (int i = 1; i <= n; i++) {
		cin >> x.a[0][i];
		x.a[0][i] %= P;
	}
	for (int i = 0; i <= n; i++) {
		y.a[0][i] = 10;
		y.a[n+1][i] = 1;
	}
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			y.a[i][j] = 1;
	y.a[n+1][n+1] = 1;
	cout << mul(x, ksm(y, m)).a[0][n] << endl;
}

int main() {
	while (cin >> n >> m) Matrix();
	return 0;
}
