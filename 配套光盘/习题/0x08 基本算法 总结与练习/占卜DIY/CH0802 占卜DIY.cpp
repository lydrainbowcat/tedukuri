//Author:XuHt
#include <cstring>
#include <iostream>
using namespace std;
char s[14][5];
int f[100], ans[13];

int main() {
	for (int i = 1; i <= 13; i++) {
		for (int j = 1; j <= 4; j++)
			cin >> s[i][j];
	}
	f['A'] = 1;
	for (int i = '2'; i <= '9'; i++) f[i] = i - '0';
	f['0'] = 10;
	f['J'] = 11;
	f['Q'] = 12;
	f['K'] = 13;
	memset(ans, 0, sizeof(ans));
	for (int i = 1; i <= 4; i++) {
		int t = s[13][i];
		while (f[t] != 13 && ans[f[t]] < 4) {
			ans[f[t]]++;
			int temp = s[f[t]][4];
			for (int j = 4; j > 1; j--) s[f[t]][j] = s[f[t]][j-1];
			t = s[f[t]][1] = temp;
		}
	}
	for (int i = 1; i <= 12; i++)
		if (ans[i] == 4) ans[0]++;
	cout << ans[0] << endl;
	return 0;
}
