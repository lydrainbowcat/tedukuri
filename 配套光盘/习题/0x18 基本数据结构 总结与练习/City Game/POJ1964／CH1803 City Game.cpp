//Author:XuHt
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006;
bool a[N][N];
int t, n, m, h[N], st[N], width[N];

int ddz(int k) {
	int ans = 0, top = 0;
	for (int i = 1; i <= m; i++)
		if (a[k][i]) h[i]++;
		else h[i] = 0;
	for (int i = 1; i <= m + 1; i++) {
		if (st[top] < h[i]) {
			st[++top] = h[i];
			width[top] = 1;
			ans = max(ans, h[i]);
		} else {
			int num = 0;
			while (top && st[top] >= h[i]) {
				num += width[top];
				ans = max(ans, st[top--] * num);
			}
			st[++top] = h[i];
			width[top] = ++num;
			ans = max(ans, st[top] * width[top]);
		}
	}
	return ans;
}

void City_Game() {
	memset(h, 0, sizeof(h));
	memset(st, 0, sizeof(st));
	memset(width, 0, sizeof(width));
	memset(a, 0, sizeof(a));
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c;
			cin >> c;
			a[i][j] = (c == 'F' ? 1 : 0);
		}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, ddz(i));
	cout << 3 * ans << endl;
}

int main() {
	cin >> t;
	while (t--) City_Game();
	return 0;
}
