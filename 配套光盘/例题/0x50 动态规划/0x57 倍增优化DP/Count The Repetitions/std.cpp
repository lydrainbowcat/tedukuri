#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>
#include<string>
using namespace std;
string s1, s2;
int n1, n2;
long long f[105][32];

void solve() {
	memset(f, 0, sizeof(f));
	for (int i = 0; i < s1.size(); i++) {
		int pos = i;
		f[i][0] = 0;
		for (int j = 0; j < s2.size(); j++) {
			int cnt = 0;
			while (s1[pos] != s2[j]) {
				pos = (pos + 1) % s1.size();
				if (++cnt >= s1.size()) { 
					cout << 0 << endl; 
					return;
				}
			}
			pos = (pos + 1) % s1.size();
			f[i][0] += cnt + 1;
		}
	}
	for (int j = 1; j <= 30; j++)
		for (int i = 0; i < s1.size(); i++)
			f[i][j] = f[i][j - 1] + f[(i + f[i][j - 1]) % s1.size()][j - 1];
	long long m = 0;
	for (int st = 0; st < s1.size(); st++) {
		long long x = st, ans = 0;
		for (int k = 30; k >= 0; k--) {
			if (x + f[x%s1.size()][k] <= s1.size()*n1) {
				x += f[x%s1.size()][k];
				ans += 1 << k;
			}
		}
		m = max(m, ans);
	}
	cout << m / n2 << endl;
}

int main()  {
	while(cin >> s2 >> n2 >> s1 >> n1) solve();
}
