#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;
// 1999999999 = 82
int f[11][83][83][83];
int pwr[11][83]; // 10^i % k

inline int mod(int x, int k) {
	return (x%k + k) % k;
}

int count(int R) {
	int a[11], n;
	for (n = 0; R; R /= 10) a[++n] = R % 10;
	int ans = 0;
	for (int sum = 1; sum <= 82; sum++) {
		int t = 0;
		int q = 0;
		for (int i = n; i; i--) {
			for (int p = 0; p < a[i]; p++) {
				if (sum - t - p < 0) break;
				ans += f[i - 1][sum - t - p][sum][mod(0 - q - p * pwr[i - 1][sum], sum)];
			}
			t += a[i];
			q = (q + a[i] * pwr[i - 1][sum]) % sum;
		}
		if (t == sum && q == 0) ans++;
	}
	return ans;
}

int main() {
	for (int k = 1; k <= 82; k++) {
		pwr[0][k] = 1 % k;
		for (int i = 1; i <= 10; i++) pwr[i][k] = pwr[i - 1][k] * 10 % k;
		f[0][0][k][0] = 1;
		for (int i = 1; i <= 10; i++) {
			for (int j = 0; j <= 82; j++) {
				for (int l = 0; l < k; l++) {
					for (int p = 0; p <= 9; p++) {
						if (j - p < 0) break;
						f[i][j][k][l] += f[i - 1][j - p][k][mod(l - p * pwr[i - 1][k], k)];
					}
				}
			}
		}
	}
	int L, R;
	cin >> L >> R;
	cout << count(R) - count(L - 1) << endl;
}