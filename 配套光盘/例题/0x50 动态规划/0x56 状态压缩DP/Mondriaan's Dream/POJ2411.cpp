#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int n, m;
long long f[12][1 << 11];
bool in_s[1 << 11];

int main()  {
	while (cin >> n >> m && n) {
		for (int i = 0; i < 1 << m; i++) {
			bool cnt = 0, has_odd = 0;
			for (int j = 0; j < m; j++)
				if (i >> j & 1) has_odd |= cnt, cnt = 0;
				else cnt ^= 1;
			in_s[i] = has_odd | cnt ? 0 : 1;
		}
		f[0][0] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < 1 << m; j++) {
				f[i][j] = 0;
				for (int k = 0; k < 1 << m; k++)
					if ((j&k) == 0 && in_s[j | k])
						f[i][j] += f[i - 1][k];
			}
		cout << f[n][0] << endl;
	}
}