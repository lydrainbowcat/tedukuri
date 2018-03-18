#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, p, ans, history_match, pos[100010];
char s[100010], f[100010]; 
int main() {
	scanf("%s", s);
	n = strlen(s); p = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') f[++p] = ')', pos[p] = i;
		else if (s[i] == '[') f[++p] = ']', pos[p] = i;
		else if (s[i] == '{') f[++p] = '}', pos[p] = i;
		else {
			if (p && s[i] == f[p]) {
				int cur_match = i - pos[p] + 1;
				if (p == 1) {
					ans = max(ans, history_match + cur_match);
					history_match += cur_match; 
				}
				else
					ans = max(ans, cur_match);
				p--;
			}
			else history_match = p = 0;
		}
	}
	cout << ans << endl;
}
