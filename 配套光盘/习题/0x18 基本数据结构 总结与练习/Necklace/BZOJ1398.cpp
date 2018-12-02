#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
char a[2000010], b[2000010];

int calc_min(char *s) {
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++) s[n+i] = s[i];
	int i = 1, j = 2, k;
	while (i <= n && j <= n) {
		for (k = 0; k < n && s[i+k] == s[j+k]; k++);
		if (k == n) break;
		if (s[i+k] > s[j+k]) {
			i = i + k + 1;
			if (i == j) i++;
		} else {
			j = j + k + 1;
			if (i == j) j++;
		}
	}
	return min(i, j);
}

int main() {
	scanf("%s", a + 1);
	int n = strlen(a + 1), x = calc_min(a);
	scanf("%s", b + 1);
	int m = strlen(b + 1), y = calc_min(b);
	a[x + n] = b[y + m] = 0;
	if (n == m && !strcmp(a + x, b + y)) {
		puts("Yes");
		puts(a + x);
	}
	else puts("No");
}