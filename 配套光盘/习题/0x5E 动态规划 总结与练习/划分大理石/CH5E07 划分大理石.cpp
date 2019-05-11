//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int a[7], k[200], num, f[60006], p[21];

int main() {
	p[0] = 0;
	for (int i = 1; i <= 20; i++) p[i] = ((p[i-1] + 1) << 1) - 1;
	while (1) {
		int s = 0;
		for (int i = 1; i <= 6; i++) {
			cin >> a[i];
			s += a[i] * i;
		}
		if (!a[1] && !a[2] && !a[3] && !a[4] && !a[5] && !a[6]) break;
		if (s & 1) {
			puts("Can't");
			continue;
		}
		num = 0;
		for (int i = 1; i <= 6; i++) {
			int t = upper_bound(p, p + 20, a[i]) - p;
			--t;
			for (int j = 0; j < t; j++) k[++num] = (p[j] + 1) * i;
			if (a[i] - p[t]) k[++num] = a[i] - p[t];
		}
		memset(f, 0, sizeof(f));
		f[0] = 1;
		for (int i = 1; i <= num; i++)
			for (int j = s >> 1; j >= k[i]; j--)
				f[j] += f[j-k[i]];
		puts(f[s/2] ? "Can" : "Can't");
	}
	return 0;
}
