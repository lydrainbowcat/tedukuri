//Author:XuHt
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
const int N = 200, L = 21;
ll f[L][N][N][2];
int n[L];

ll calc(ll x, int P) {
	if (!x) return 0;
	memset(f, 0, sizeof(f));
	int t = 0;
	while (x) {
		n[++t] = x % 10;
		x /= 10;
	}
	f[t+1][0][0][0] = 1;
	for (int i = t + 1; i > 1; i--)
		for (int j = 0; j <= P; j++)
			for (int k = 0; k < P; k++)
				if (f[i][j][k][0] || f[i][j][k][1])
					for (int p = 0; p < 10; p++) {
						int w = (10 * k + p) % P;
						if (p < n[i-1] && j + p <= P)
							f[i-1][j+p][w][1] += f[i][j][k][0];
						else if (p == n[i-1] && j + p <= P)
							f[i-1][j+p][w][0] += f[i][j][k][0];
						if (f[i][j][k][1] && j + p <= P)
							f[i-1][j+p][w][1] += f[i][j][k][1];
					}
	return f[1][P][0][0] + f[1][P][0][1];
}

int main() {
	ll a, b, ans = 0;
	cin >> a >> b;
	for (int i = 1; i <= 9 * 18; i++)
		ans += calc(b, i) - calc(a - 1, i);
	cout << ans << endl;
	return 0;
}
