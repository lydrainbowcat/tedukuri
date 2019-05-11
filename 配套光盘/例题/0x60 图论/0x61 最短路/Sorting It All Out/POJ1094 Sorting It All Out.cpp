//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 30;
int n, m, d[N][N], e[N][N];

int floyd() {
	memcpy(e, d, sizeof(e));
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				e[i][j] |= e[i][k] & e[k][j];
				if (e[i][j] == e[j][i] && e[i][j] && i != j) return -1;
			}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (e[i][j] == e[j][i] && !e[i][j] && i != j) return 0;
	return 1;
}

void Sorting_It_All_Out() {
	memset(d, 0, sizeof(d));
	bool flag = 1;
	for (int i = 1; i <= m; i++) {
		char s[6];
		scanf("%s", s);
		d[s[0]-'A'][s[2]-'A'] = 1;
		if (flag) {
			int now = floyd();
			if (now == -1) {
				printf("Inconsistency found after %d relations.\n", i);
				flag = 0;
			} else if (now == 1) {
				printf("Sorted sequence determined after %d relations: ", i);
				pair<int, char> ans[N];
				for (int j = 0; j < n; j++) {
					ans[j].first = 0;
					ans[j].second = 'A' + j;
				}
				for (int j = 0; j < n; j++)
					for (int k = 0; k < n; k++)
						if (e[j][k]) ++ans[j].first;
				sort(ans, ans + n);
				for (int j = n - 1; j >= 0; j--) printf("%c", ans[j].second);
				puts(".");
				flag = 0;
			}
		}
	}
	if (flag) puts("Sorted sequence cannot be determined.");
}

int main() {
	while (cin >> n >> m && n) Sorting_It_All_Out();
	return 0;
}
