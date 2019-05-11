#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct { int l, r, ans; } query[10010];
int a[20010], fa[20010], d[20010], n, m, t;
void read_discrete() { // 读入、离散化
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		char str[5];
		scanf("%d%d%s", &query[i].l, &query[i].r, str);
		query[i].ans = (str[0] == 'o' ? 1 : 0);
		a[++t] = query[i].l - 1;
		a[++t] = query[i].r;
	}
	sort(a + 1, a + t + 1);
	n = unique(a + 1, a + t + 1) - a - 1;
}
int get(int x) {
	if (x == fa[x]) return x;
	int root = get(fa[x]);
	d[x] ^= d[fa[x]];
	return fa[x] = root;
}
int main() {
	read_discrete();
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		// 求出l-1和r离散化之后的值
		int x = lower_bound(a + 1, a + n + 1, query[i].l - 1) - a;
		int y = lower_bound(a + 1, a + n + 1, query[i].r) - a;
		// 执行get函数，得到树根，并进行路径压缩
		int p = get(x), q = get(y);
		if (p == q) { // 已经在同一集合内
			if ((d[x] ^ d[y]) != query[i].ans) { // 矛盾，输出
				cout << i - 1 << endl;
				return 0;
			}
		}
		else { // 不在同一集合，合并
			fa[p] = q;
			d[p] = d[x] ^ d[y] ^ query[i].ans;
		}
	}
	cout << m << endl; // 没有矛盾
}