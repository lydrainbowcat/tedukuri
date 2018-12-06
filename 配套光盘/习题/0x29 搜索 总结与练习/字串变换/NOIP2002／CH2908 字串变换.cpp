//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 10006;
struct Node {
	char s[36];
	int ans;
} q1[N], q2[N];
char a[7][26] , b[7][26];
int n;

bool pd(char *s1, char *s2) {
	if (strlen(s1) != strlen(s2)) return 0;
	for (unsigned int i = 0; i < strlen(s1); i++)
		if (s1[i] != s2[i]) return 0;
	return 1;
}

bool judge(char *str, int num, bool flag) {
	char *now = (flag ? a[num] : b[num]);
	for (unsigned int i = 0; i < strlen(now); i++)
		if (now[i] != str[i]) return 0;
	return 1;
}

void bfs() {
	int l1 = 1, r1 = 1, l2 = 1, r2 = 1;
	while (l1 <= r1 && l2 <= r2) {
		if (q1[l1].ans + q2[l2].ans > 10) {
			puts("NO ANSWER!");
			return;
		}
		for (unsigned int i = 0; i < strlen(q1[l1].s); i++)
			for (int j = 1; j < n; j++)
				if (judge(q1[l1].s + i, j, 1)) {
					r1++;
					unsigned int k = 0, l = 0;
					while (k < i) {
						q1[r1].s[k] = q1[l1].s[k];
						++k;
					}
					while (l < strlen(b[j])) q1[r1].s[k++] = b[j][l++];
					l = i + strlen(a[j]);
					while (l <= strlen(q1[l1].s)) q1[r1].s[k++] = q1[l1].s[l++];
					q1[r1].s[k] = 0;
					q1[r1].ans = q1[l1].ans + 1;
					for (int w = 1; w <= r1; w++)
						if (pd(q1[r1].s, q2[w].s)) {
							cout << q1[r1].ans + q2[w].ans << endl;
							return;
						}
				}
		for (unsigned int i = 0; i < strlen(q2[l2].s); i++)
			for (int j = 1; j < n; j++)
				if (judge(q2[l2].s + i, j, 0)) {
					r2++;
					unsigned int k = 0, l = 0;
					while (k < i) {
						q2[r2].s[k] = q2[l2].s[k];
						++k;
					}
					while (l < strlen(a[j])) q2[r2].s[k++] = a[j][l++];
					l = i+strlen(b[j]);
					while (l <= strlen(q2[l2].s)) q2[r2].s[k++] = q2[l2].s[l++];
					q2[r2].s[k] = 0;
					q2[r2].ans = q2[l2].ans + 1;
					for (int w = 1; w <= r1; w++)
						if (pd(q2[r2].s, q1[w].s)) {
							cout << q1[w].ans + q2[r2].ans << endl;
							return;
						}
				}
		++l1;
		++l2;
	}
	puts("NO ANSWER!");
}

int main() {
	cin >> q1[1].s >> q2[1].s;
	n = 1;
	while (cin >> a[n] >> b[n]) ++n;
	q1[1].ans = q2[1].ans = 0;
	bfs();
	return 0;
}
