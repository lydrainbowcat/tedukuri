//Author:XuHt
#include <iostream>
using namespace std;
const int L = 12, D = 36, P = 11380;
int f[L][L][L][D], s[L][L][L][D];

int main() {
	int l1, l2, l3, d, x;
	cin >> l1 >> l2 >> l3 >> d;
	f[0][0][0][0] = s[0][0][0][0] = 1;
	for (int i = 0; i <= l1; i++)
		for (int j = 0; j <= l2; j++)
			for (int k = 0; k <= l3; k++) {
				for (int l = 1; l <= d; l++)
					if (i + j + k < l) f[i][j][k][l] = 0;
					else {
						if (i) x = f[i-1][j][k][l-1];
						else if (j) x = f[0][j-1][k][l-1];
						else if (k) x = f[0][0][k-1][l-1];
						else x = 0;
						for (int ii = 0; ii <= i; ii++)
							for (int jj = 0; jj <= j; jj++)
								for (int kk = 0; kk <= k; kk++)
									if (ii + jj + kk && ii + jj + kk != i + j + k) {
										if (ii) {
											if (l >= 2) x = (x + s[ii-1][jj][kk][l-2] * f[i-ii][j-jj][k-kk][l]) % P;
											x = (x + f[ii-1][jj][kk][l-1] * s[i-ii][j-jj][k-kk][l]) % P;
										} else if (jj) {
											if (l >= 2) x = (x + s[0][jj-1][kk][l-2] * f[i][j-jj][k-kk][l]) % P;
											x = (x + f[0][jj-1][kk][l-1] * s[i][j-jj][k-kk][l]) % P;
										} else {
											if (l >= 2) x = (x + s[0][0][kk-1][l-2] * f[i][j][k-kk][l]) % P;
											x = (x + f[0][0][kk-1][l-1] * s[i][j][k-kk][l]) % P;
										}
									}
						f[i][j][k][l] = x;
					}
				for (int l = 1; l <= d; l++) s[i][j][k][l] = (s[i][j][k][l-1] + f[i][j][k][l]) % P;
			}
	cout << f[l1][l2][l3][d] << endl;
	return 0;
}
