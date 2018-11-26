//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1006;
int f[200], ff[100];
char s[N], ans[N];

void NUMBER_BASE_CONVERSION() {
	int a, b;
	cin >> a >> b;
	scanf("%s", s);
	cout << a << " " << s << endl << b << " ";
	int len = strlen(s), t = strlen(s), i;
	for (i = 0; t; i++) {
		int k = 0;
		for (int j = len - t; j < len; j++) {
			k = k * a + f[(int)s[j]];
			s[j] = ff[k/b];
			k %= b;
		}
		ans[i] = ff[k];
		while (t > 0 && s[len-t] == '0') t--;
	}
	while (--i >= 0) cout << ans[i];
	cout << endl << endl;
}

int main() {
	int t = 0;
	for (int i = '0'; i <= '9'; i++) {
		f[i] = t;
		ff[t++] = i;
	}
	for (int i = 'A'; i <= 'Z'; i++) {
		f[i] = t;
		ff[t++] = i;
	}
	for (int i = 'a'; i <= 'z'; i++) {
		f[i] = t;
		ff[t++] = i;
	}
	cin >> t;
	while (t--) NUMBER_BASE_CONVERSION();
	return 0;
}
