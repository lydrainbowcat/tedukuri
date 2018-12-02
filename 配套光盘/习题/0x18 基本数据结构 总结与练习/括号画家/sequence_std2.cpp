//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100006;
char s[N], st[N];
int top = 0, ans = 0, num = 0;

void gx() {
	ans = max(ans, num);
	num = top = 0;
}

int main() {
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	for (int i = 1; i <= len; i++) {
		if (s[i] == '(' || s[i] == '[' || s[i] == '{') st[++top] = s[i];
		else if ((s[i] == ')' && st[top] == '(' || s[i] == ']' && st[top] == '[' || s[i] == '}' && st[top] == '{')) {
			++num;
			--top;
		}
		else gx();
	}
	gx();
	cout << (ans << 1) << endl;
	return 0;
}
