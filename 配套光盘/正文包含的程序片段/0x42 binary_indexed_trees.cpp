// [1,x]分成的O(log(x))个小区间
while (x > 0) {
	printf("[%d, %d]\n", x - (x & -x) + 1, x);
	x -= x & -x;
}

// 树状数组查询前缀和
int ask(int x) {
	int ans = 0;
	for (; x; x -= x & -x) ans += c[x];
	return ans;
}

// 树状数组单点增加
void add(int x, int y) {
	for (; x <= N; x += x & -x) c[x] += y;
}

// 树状数组求逆序对
for (int i = n; i; i--) {
	ans += ask(a[i]);
	add(a[i], 1);
}
