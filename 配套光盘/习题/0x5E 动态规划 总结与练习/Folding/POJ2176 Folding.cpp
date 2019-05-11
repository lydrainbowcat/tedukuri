//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 106, INF = 0x3f3f3f3f;
struct F {
	char s[N];
	int len;
} f[N][N];
char s[N];

int main() {
	scanf("%s", s);
	int n = strlen(s);
	for (int i = 0; i < n; i++) {
		f[i][i].len = 1;
		f[i][i].s[0] = s[i];
	}
	for (int len = 2; len <= n; len++)
		for (int l = 0; l + len <= n; l++) {
			int r = l + len - 1;
			f[l][r].len = INF;
			for (int i = 1; i <= len >> 1; i++) {
				if (len % i) continue;
				int L = l, R = l + i;
				while (R <= r && s[L++] == s[R]) ++R;
				if (R > r) {
					sprintf(f[l][r].s, "%d", len / i);
					strcat(f[l][r].s, "(");
					strcat(f[l][r].s, f[l][l+i-1].s);
					strcat(f[l][r].s, ")");
					f[l][r].len = strlen(f[l][r].s);
					break;
				}
			}
			for (int i = l; i < r; i++)
				if (f[l][r].len > f[l][i].len + f[i+1][r].len) {
					f[l][r].len = f[l][i].len + f[i+1][r].len;
					strcpy(f[l][r].s, f[l][i].s);
					strcat(f[l][r].s, f[i+1][r].s);
				}
		}
	puts(f[0][n-1].s);
	return 0;
}
