#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100], n, t, ans;
int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1, j; i <= n; i++) {
			scanf("%d", &j);
			a[i] ^= j;
			a[i] |= 1 << i; // a[i][i] = 1;-
		}
		int x, y;
		while (~scanf("%d%d", &x, &y) && x && y) {
			a[y] |= 1 << x; // a[y][x] = 1;
		}
		ans = 1;
		for (int i = 1; i <= n; i++) {
			// 找到最大的一个a[i]，即主元位数最高的a[i] 
			for (int j = i + 1; j <= n; j++)
				if (a[j] > a[i]) swap(a[i], a[j]);
			// 消元完毕，有i-1个主元，n-i+1个自由元 
			if (a[i] == 0) { ans = 1 << (n - i + 1); break; }
			// 出现0=1的方程，无解
			if (a[i] == 1) { ans = 0; break; }
			// a[i]最高位的1作为主元，消去其他方程该位的系数 
			for (int k = n; k; k--)
				if (a[i] >> k & 1) {
					for (int j = 1; j <= n; j++)
						if (i != j && (a[j] >> k & 1)) a[j] ^= a[i];
					break;
				}
		}
		if (ans == 0) puts("Oh,it's impossible~!!");
		else cout << ans << endl; 
	}
}