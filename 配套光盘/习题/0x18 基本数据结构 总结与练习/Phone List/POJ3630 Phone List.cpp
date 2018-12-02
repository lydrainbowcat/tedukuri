//Author:XuHt
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10006;
string s[N];
int n;

bool pd() {
	for (int i = 1; i < n; i++) {
		int len = s[i].size(), j;
		for (j = 1; j <= len; j++)
			if (s[i][j] != s[i+1][j]) break;
		if (j == len) return 1;
	}
	return 0;
}

void Phone_List() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i];
	sort(s + 1, s + n + 1);
	cout << (pd() ? "NO" : "YES") << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) Phone_List();
	return 0;
}
