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

// 动态开点的线段树
struct SegmentTree {
    int lc, rc; // 左右子节点的编号
	int dat;
} tr[SIZE * 2];
int root, tot;

int build() { // 新建一个节点
	tot++;
	tr[tot].lc = tr[tot].rc = tr[tot].dat = 0;
	return tot;
}

// 在main函数中
tot = 0;
root = build(); // 根节点

// 单点修改，在val位置加delta，维护区间最大值
void insert(int p, int l, int r, int val, int delta) {
    if (l == r) {
        tr[p].dat += delta;
        return;
    }
    int mid = (l + r) >> 1; // 代表的区间[l,r]作为递归参数传递
    if (val <= mid) {
        if (!tr[p].lc) tr[p].lc = build(); // 左子树不存在，动态开点
        insert(tr[p].lc, l, mid, val, delta);
    }
    else {
        if (!tr[p].rc) tr[p].rc = build(); // 右子树不存在，动态开点
        insert(tr[p].rc, mid + 1, r, val, delta);
    }
    tr[p].dat = max(tr[tr[p].lc].dat, tr[tr[p].rc].dat);
}

// 调用
insert(root, 1, n, val, delta);

// 合并两棵线段树
int merge(int p, int q, int l, int r) {
    if (!p) return q; // p,q之一为空
    if (!q) return p;
    if (l == r) { // 到达叶子
        tr[p].dat += tr[q].dat;
        return p;
    }
    int mid = (l + r) >> 1;
    tr[p].lc = merge(tr[p].lc, tr[q].lc, l, mid); // 递归合并左子树
    tr[p].rc = merge(tr[p].rc, tr[q].rc, mid + 1, r); // 递归合并右子树
    tr[p].dat = max(tr[tr[p].lc].dat, tr[tr[p].rc].dat); // 更新最值
    return p; // 以p为合并后的节点，相当于删除q
}
