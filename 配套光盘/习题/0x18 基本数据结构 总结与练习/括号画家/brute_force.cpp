#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, p, ans, len, f[100010];
char s[100010]; 
int main() {
	scanf("%s", s);
	n = strlen(s); p = 0;
	for (int i = 0; i < n; i++) {
		p = 0;
		for (int j = i; j < n; j++) {
			if (s[j] == '(') f[++p] = ')';
			else if (s[j] == '[') f[++p] = ']';
			else if (s[j] == '{') f[++p] = '}';
			else if (!p || s[j] != f[p]) break;
			else {
				p--;
				if (!p) ans = max(ans, j - i + 1);
			}
		}
	}
	cout << ans << endl;
}
