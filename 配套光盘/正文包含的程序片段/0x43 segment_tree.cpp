struct SegmentTree {
	int l, r;
	int dat;
} t[SIZE * 4]; // struct数组存储线段树

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r; // 节点p代表区间[l,r]
	if (l == r) { t[p].dat = a[l]; return; } // 叶节点
	int mid = (l + r) / 2; // 折半
	build(p*2, l, mid); // 左子节点[l,mid]，编号p*2
	build(p*2+1, mid+1, r); // 右子节点[mid+1,r]，编号p*2+1
	t[p].dat = max(t[p*2].dat, t[p*2+1].dat); // 从下往上传递信息
}

build(1, 1, n); // 调用入口

void change(int p, int x, int v) {
	if (t[p].l == t[p].r) { t[p].dat = v; return; } // 找到叶节点
	int mid = (t[p].l + t[p].r) / 2;
	if (x <= mid) change(p*2, x, v); // x属于左半区间
	else change(p*2+1, x, v); // x属于右半区间
	t[p].dat = max(t[p*2].dat, t[p*2+1].dat); // 从下往上更新信息
}

change(1, x, v); // 调用入口

int ask(int p, int l, int r) {
	if (l <= t[p].l && r >= t[p].r) return t[p].dat; // 完全包含，直接返回
	int mid = (t[p].l + t[p].r) / 2;
	int val = 0;
	if (l <= mid) val = max(val, ask(p*2, l, r)); // 左子节点有重叠
	if (r > mid) val = max(val, ask(p*2+1, l, r)); // 右子节点有重叠
	return val;
}

cout << ask(1, l, r) << endl; // 调用入口
