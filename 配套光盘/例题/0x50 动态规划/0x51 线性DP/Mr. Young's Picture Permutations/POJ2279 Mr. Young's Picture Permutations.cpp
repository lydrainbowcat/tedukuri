//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
int n[6], k;

void work() {
	for (int i = 1; i <= k; i++) cin >> n[i];
	while (k < 5) n[++k] = 0;
	ll f[n[1]+1][n[2]+1][n[3]+1][n[4]+1][n[5]+1];
	memset(f, 0, sizeof(f));
	f[0][0][0][0][0] = 1;
	for (int i = 0; i <= n[1]; i++)
		for (int j = 0; j <= n[2]; j++)
			for (int k = 0; k <= n[3]; k++)
				for (int l = 0; l <= n[4]; l++)
					for (int m = 0; m <= n[5]; m++) {
						if (i < n[1]) f[i+1][j][k][l][m] += f[i][j][k][l][m];
						if (j < n[2] && i > j) f[i][j+1][k][l][m] += f[i][j][k][l][m];
						if (k < n[3] && j > k) f[i][j][k+1][l][m] += f[i][j][k][l][m];
						if (l < n[4] && k > l) f[i][j][k][l+1][m] += f[i][j][k][l][m];
						if (m < n[5] && l > m) f[i][j][k][l][m+1] += f[i][j][k][l][m];
					}
	cout << f[n[1]][n[2]][n[3]][n[4]][n[5]] << endl;
}

int main() {
	while (cin >> k && k) work();
	return 0;
}
