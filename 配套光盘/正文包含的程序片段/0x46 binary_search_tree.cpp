struct BST {
	int l, r; // 左右子节点在数组中的下标
	int val;  // 节点关键码
} a[SIZE]; // 数组模拟链表
int tot, root, INF = 1<<30;

int New(int val) {
	a[++tot].val = val;
	return tot;
}

void Build() {
	New(-INF), New(INF);
	root = 1, a[1].r = 2;
}

int Get(int p, int val) {
	if (p == 0) return 0; // 检索失败
	if (val == a[p].val) return p; // 检索成功
	return val < a[p].val ? Get(a[p].l, val) : Get(a[p].r, val);
}

void Insert(int &p, int val) {
	if (p == 0) {
		p = New(val); // 注意p是引用，其父节点的l或r值会被同时更新
		return;
	}
	if (val == a[p].val) return;
	if (val < a[p].val) Insert(a[p].l, val);
	else Insert(a[p].r, val);
}

int GetNext(int val) {
	int ans = 2; // a[2].val==INF
	int p = root;
	while (p) {
		if (val == a[p].val) { // 检索成功
			if (a[p].r > 0) { // 有右子树
				p = a[p].r;
				// 右子树上一直向左走
				while (a[p].l > 0) p = a[p].l;
				ans = p;
			}
			break;
		}
		// 每经过一个节点，都尝试更新后继
		if (a[p].val > val && a[p].val < a[ans].val) ans = p;
		p = val < a[p].val ? a[p].l : a[p].r;
	}
	return ans;
}

void Remove(int &p, int val) { // 从子树p中删除值为val的节点
	if (p == 0) return;
	if (val == a[p].val) { // 已经检索到值为val的节点
		if (a[p].l == 0) { // 没有左子树
			p = a[p].r; // 右子树代替p的位置，注意p是引用
		}
		else if (a[p].r == 0) { // 没有右子树
			p = a[p].l; // 左子树代替p的位置，注意p是引用
		}
		else { // 既有左子树又有右子树
			// 求后继节点
			int next = a[p].r;
			while (a[next].l > 0) next = a[next].l;
			// next一定没有左子树，直接删除
			Remove(a[p].r, a[next].val);
			// 令节点next代替节点p的位置
			a[next].l = a[p].l, a[next].r = a[p].r;
			p = next; // 注意p是引用
		}
		return;
	}
	if (val < a[p].val) {
		Remove(a[p].l, val);
	} else {
		Remove(a[p].r, val);
	}
}

void zig(int &p) {
	int q = a[p].l;
	a[p].l = a[q].r, a[q].r = p;
	p = q; // 注意p是引用
}

void zag(int &p) {
	int q = a[p].r;
	a[p].r = a[q].l, a[q].l = p;
	p = q; // 注意p是引用
}
