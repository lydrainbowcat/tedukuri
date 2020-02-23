#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, p, ans, history_match[100010], pos[100010];
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
				// 清空更深层的历史数据 
				history_match[p] = 0;
				p--;
				// 更新当前层的历史数据，同层历史数据可以累加 
				ans = max(ans, history_match[p] + cur_match);
				history_match[p] += cur_match;
			}
			else {
				for (int j = 0; j <= p; j++) history_match[j] = 0;
				p = 0;
			}
		}
	}
	cout << ans << endl;
}
