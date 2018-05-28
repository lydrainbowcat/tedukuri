// 可持久化Trie，例题：BZOJ3261
const int N = 600010;
int trie[N*24][2], latest[N*24]; // latest和end可合并为一个数组
int s[N], root[N], n, m, tot;
// 本题需要统计子树latest，故使用递归插入s[i]，当前为s[i]的第k位
void insert(int i, int k, int p, int q) {
	if (k < 0) {
		latest[q] = i;
		return;
	}
	int c = s[i] >> k & 1;
	if (p) trie[q][c ^ 1] = trie[p][c ^ 1];
	trie[q][c] = ++tot;
	insert(i, k - 1, trie[p][c], trie[q][c]);
	latest[q] = max(latest[trie[q][0]], latest[trie[q][1]]);
}

int ask(int now, int val, int k, int limit) {
	if (k < 0) return s[latest[now]] ^ val;
	int c = val >> k & 1;
	if (latest[trie[now][c ^ 1]] >= limit)
		return ask(trie[now][c ^ 1], val, k - 1, limit);
	else
		return ask(trie[now][c], val, k - 1, limit);
}

int main() {
	cin >> n >> m;
	latest[0] = -1;
	root[0] = ++tot;
	insert(0, 23, 0, root[0]);
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		s[i] = s[i - 1] ^ x;
		root[i] = ++tot;
		insert(i, 23, root[i - 1], root[i]);
	}
	for (int i = 1; i <= m; i++) {
		char op[2]; scanf("%s", op);
		if (op[0] == 'A') {
			int x; scanf("%d", &x);
			root[++n] = ++tot;
			s[n] = s[n - 1] ^ x;
			insert(n, 23, root[n - 1], root[n]);
		}
		else {
			int l, r, x; scanf("%d%d%d", &l, &r, &x);
			printf("%d\n", ask(root[r - 1], x ^ s[n], 23, l - 1));
		}
	}
}


// 可持久化线段树，建树
struct SegmentTree {
    int lc, rc; // 左右子节点编号
    int dat; // 区间最大值
} tree[MAX_MLOGN];
int tot, root[MAX_M]; // 可持久化线段树的总点数和每个根
int n, a[MAX_N];

int build(int l, int r) {
    int p = ++tot;
    if (l == r) { tree[p].dat = a[l]; return p; }
    int mid = (l + r) >> 1;
    tree[p].lc = build(l, mid);
    tree[p].rc = build(mid + 1, r);
    tree[p].dat = max(tree[tree[p].lc].dat, tree[tree[p].rc].dat);
    return p;
}
// 在main函数中
root[0] = build(1, n);


// 可持久化线段树，单点修改
int insert(int now, int l, int r, int x, int val) {
    int p = ++tot;
    tree[p] = tree[now]; 
    if (l == r) {
        tree[p].dat = val; 
        return p;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) 
tree[p].lc = insert(tree[now].lc, l, mid, x, val);
    else 
tree[p].rc = insert(tree[now].rc, mid + 1, r, x, val);
    tree[p].dat = max(tree[tree[p].lc].dat, tree[tree[p].rc].dat);
    return p;
}
// 在main函数中
root[i] = insert(root[i - 1], 1, n, x, val);


// 可持久化线段树，例题：POJ2104 K-th Number，查询部分
// 在p, q两个节点上，值域为 [l,r]，求第k小数
int ask(int p, int q, int l, int r, int k) {
    if (l == r) return l; // 找到答案
    int mid = (l + r) >> 1;
    // 有多少个数落在值域 [l,mid] 内
    int lcnt = tree[tree[p].lc].cnt - tree[tree[q].lc].cnt;
    if (k <= lcnt) return ask(tree[p].lc, tree[q].lc, l, mid, k);
    else return ask(tree[p].rc, tree[q].rc, mid + 1, r, k - lcnt);
}
// 在main函数中，询问为(li,ri,ki)
int ans = ask(root[ri], root[li - 1], 1, t, ki);
