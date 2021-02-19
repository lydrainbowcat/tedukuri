#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N = 105;
int a[N], b[N], c[N], d[N];
double w[N][N]; // 边权
double la[N], lb[N]; // 左、右部点的顶标
bool va[N], vb[N]; // 访问标记：是否在交错树中
int match[N], ans[N]; // 右部点匹配了哪一个左部点
int n;
double upd[N], delta;

bool dfs(int x) {
	va[x] = 1; // 访问标记：x在交错树中
	for (int y = 1; y <= n; y++)
		if (!vb[y])
			if (fabs(la[x] + lb[y] - w[x][y]) < 1e-8) { // 相等子图
				vb[y] = 1; // 访问标记：y在交错树中
				if (!match[y] || dfs(match[y])) {
					match[y] = x;
					return true;
				}
			}
			else upd[y] = min(upd[y], la[x] + lb[y] - w[x][y]);
	return false;
}

void KM() {
	for (int i = 1; i <= n; i++) {
		la[i] = -1e10; // -inf
		lb[i] = 0;
		for (int j = 1; j <= n; j++)
			la[i] = max(la[i], w[i][j]);
	}
	for (int i = 1; i <= n; i++)
		while (true) { // 直到左部点找到匹配
			memset(va, 0, sizeof(va));
			memset(vb, 0, sizeof(vb));
			delta = 1e10; // inf
			for (int j = 1; j <= n; j++) upd[j] = 1e10; 
			if (dfs(i)) break;
			for (int j = 1; j <= n; j++)
				if (!vb[j]) delta = min(delta, upd[j]);
			for (int j = 1; j <= n; j++) { // 修改顶标
				if (va[j]) la[j] -= delta;
				if (vb[j]) lb[j] += delta;
			}
		}
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
	for (int i = 1; i <= n; i++) scanf("%d%d", &c[i], &d[i]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			w[i][j] = -sqrt((a[i]-c[j])*(a[i]-c[j])*1.0+(b[i]-d[j])*(b[i]-d[j])*1.0);
	KM();
	for (int i = 1; i <= n; i++) ans[match[i]] = i;
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
