#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int u = 1000010;
struct rec { int x, y, z; };
rec a[u]; // 原始问题的操作序列（长度为n+m）
rec b[u]; // 静态问题的坐标（按横坐标排序）及其在a中的下标
int c[u], tot; // 树状数组、坐标的最大范围
int ans[u], n, m, t;

bool operator <(const rec &a, const rec &b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

int ask(int x) {
	int y = -(1 << 30);
	for (; x; x -= x & -x) y = max(y, c[x]);
	return y;
}

void insert(int x, int y) {
	for (; x < tot; x += x & -x) c[x] = max(c[x], y);
}

// 求解简化版问题，需要考虑b[st~ed]的坐标，根据4个方向的不同，
// 横坐标顺序为de(±1)，树状数组维护的信息用系数dx,dy(±1)指定
void calc(int st, int ed, int de, int dx, int dy) {
	for (int i = st; i != ed; i += de) {
		int y = dy == 1 ? b[i].y : tot - b[i].y;
		int temp = dx*b[i].x + dy*b[i].y;
		if (a[b[i].z].z == 1) insert(y, temp);
		else ans[b[i].z] = min(ans[b[i].z], abs(temp - ask(y)));
	}
	for (int i = st; i != ed; i += de) { // 还原树状数组
		int y = dy == 1 ? b[i].y : tot - b[i].y;
		if (a[b[i].z].z == 1) // 撤销修改
			for (int j = y; j < tot; j += j & -j) c[j] = -(1 << 30);
	}
}

void cdqdiv(int l, int r) {
	int mid = (l + r) >> 1;
	if (l < mid) cdqdiv(l, mid);
	if (mid + 1 < r) cdqdiv(mid + 1, r);
	t = 0;
	for (int i = l; i <= r; i++)
		if (i <= mid && a[i].z == 1 || i > mid && a[i].z == 2)
			b[++t] = a[i], b[t].z = i;
	// 此处排序可以优化掉（放在外边并适当修改写法）
	sort(b + 1, b + t + 1);
	calc(1, t + 1, 1, 1, 1), calc(t, 0, -1, -1, -1);
	calc(1, t + 1, 1, 1, -1), calc(t, 0, -1, -1, 1);
}

int main() {
	cin >> n >> m; m += n;
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].x, &a[i].y), a[i].y++, a[i].z = 1;
	for (int i = n + 1; i <= m; i++)
		scanf("%d%d%d", &a[i].z, &a[i].x, &a[i].y), a[i].y++;
	for (int i = 1; i <= m; i++) tot = max(tot, a[i].y);
	tot++;
	memset(c, 0xcf, sizeof(c));
	memset(ans, 0x3f, sizeof(ans));
	cdqdiv(1, m);
	for (int i = 1; i <= m; i++)
		if (a[i].z == 2) printf("%d\n", ans[i]);
}
