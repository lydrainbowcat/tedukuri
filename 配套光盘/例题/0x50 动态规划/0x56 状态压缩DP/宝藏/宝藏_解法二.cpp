#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 15, M = 531441;
const int p[13] = { 1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441 }; // 3的0~12次方
int n, m, bit[N], zero[N];
int a[N][N], f[2][M];

int main() {
	cin >> n >> m;
	memset(a, 0x3f, sizeof(a));
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		a[x][y] = a[y][x] = min(a[x][y], z);
	}
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; i++) f[1][p[i - 1]] = 0;
	for (int i = 1; i <= n; i++) { // 深度
		for (int j = 1; j < M; j++) { // 状态
			if (f[i & 1][j] == 0x3f3f3f3f) continue;
			int s = j; // 所有为2的位变为1得到的状态记为s
			int last = 0; // 状态j最高位的1
			int t = 0;
			for (int x = 1, k = j; x <= n; x++, k /= 3) { // 取出j的每一位
				bit[x] = k % 3; // j的第x-1位代表节点x
				if (bit[x] == 2) s -= p[x - 1];
				else if (bit[x] == 1) last = x;
				else zero[t++] = x;
			}

			// 第1类转移：不再扩展第i层，开始扩展下一层
			f[i + 1 & 1][s] = min(f[i + 1 & 1][s], f[i & 1][j]);

			if (last) {
				// 第2类转移：在第i层扩展状态j最高位的1
				int x = last;
				while (t--) {
					int y = zero[t];
					if (a[x][y] == 0x3f3f3f3f) continue;
					s = j + 2 * p[y - 1]; // 第y-1位设为2得到的新状态
					f[i & 1][s] = min(f[i & 1][s], f[i & 1][j] + i * a[x][y]); // 转移
				}

				// 第3类转移：在第i层不扩展状态j最高位的1，但可以继续扩展其他位的1
				s = j + p[x - 1]; // 第x-1位的1变为2
				f[i & 1][s] = min(f[i & 1][s], f[i & 1][j]); // 转移
			}
			f[i & 1][j] = 0x3f3f3f3f;
		}
	}
	int s = 0;
	for (int i = 1; i <= n; i++) s += p[i - 1];
	cout << f[n + 1 & 1][s] << endl;
}
