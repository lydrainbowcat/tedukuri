//Author:XuHt
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5006;
int n, r, s[N][N];

int main() {
	memset(s, 0, sizeof(s));
	cin >> n >> r;
	while (n--) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		s[x][y] += z;
	}
	for (int i = 0; i <= 5000; i++)
		for (int j = 0; j <= 5000; j++)
			if (!i && !j) continue;
			else if (!i) s[i][j] += s[i][j-1];
			else if (!j) s[i][j] += s[i-1][j];
			else s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
	int ans = 0;
	if(r<5001){
		for (int i = r - 1; i <= 5000; i++)
			for (int j = r - 1; j <= 5000; j++)
				if (i == r - 1 && j == r - 1) ans = max(ans, s[i][j]);
				else if (i == r - 1) ans = max(ans, s[i][j] - s[i][j-r]);
				else if (j == r - 1) ans = max(ans, s[i][j] - s[i-r][j]);
				else ans = max(ans, s[i][j] - s[i-r][j] - s[i][j-r] + s[i-r][j-r]);
	}
	else{	//r>=5001，可以覆盖所有区域
		ans=s[5000][5000];
	}
	cout << ans << endl;
	return 0;
}
