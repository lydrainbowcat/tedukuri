#include<bits/stdc++.h>
using namespace std;

struct Node {
	Node* left;    // 左孩子
	Node* right;   // 右孩子
	int key, val;  // 节点关键码（原始数据）、随机权值
	int cnt, size; // 副本数、子树大小

    Node(int data) {
        key = data;
        val = rand();
        cnt = size = 1;
        left = right = nullptr;
    }
};

class Treap {
public:
    Treap() {
        // 建立一棵空Treap，包含两个保护结点
        root = new Node(-1e9);
        root->right = new Node(1e9);
        update(root);
    }

    // 插入
    void Insert(int data) {
        root = Insert(root, data);
    }

    // 删除
    void Remove(int data) {
        root = Remove(root, data);
    }

    // 查询target的排名
    int GetRankByVal(int target) {
        // 有保护结点，所以减1
        return GetRankByVal(root, target) - 1;
    }

    // 查询排第rank名的元素
    int GetValByRank(int rank) {
        // 有保护结点，所以加1
        return GetValByRank(root, rank + 1);
    }
    
    // 查找target的前驱（小于target的最大的数）
    int GetPre(int target) {
    	int ans = -1e9;
    	Node* p = root;
    	while (p) {
    		if (target == p->key) {
    		    // 检索到了target，且有左子树，应该在左子树中一直向右走
    			if (p->left) {
    				p = p->left;
    				while (p->right) p = p->right;
    				ans = p->key;
    			}
    			break;
    		}
    		// 若最终检索不到target，答案就在途径的结点中（小于target的最大的数）
    		if (p->key < target && p->key > ans) ans = p->key;
    		p = target < p->key ? p->left : p->right;
    	}
    	return ans;
    }
    
    // 查找target的后继（大于target的最小的数）
    int GetNext(int target) {
    	int ans = 1e9;
    	Node* p = root;
    	while (p) {
    		if (target == p->key) {
    		    // 检索到了target，且有右子树，应该在右子树中一直向左走
    			if (p->right) {
    				p = p->right;
    				while (p->left) p = p->left;
    				ans = p->key;
    			}
    			break;
    		}
    		// 若最终检索不到target，答案就在途径的结点中（大于target的最小的数）
    		if (p->key > target && p->key < ans) ans = p->key;
    		p = target < p->key ? p->left : p->right;
    	}
    	return ans;
    }

private:
    // 在以p为根的子树中查询target的排名
    int GetRankByVal(Node* p, int target) {
    	if (p == nullptr) return 0;
    	int left_size = p->left ? p->left->size : 0;
    	if (target == p->key) return left_size + 1;
    	if (target < p->key) return GetRankByVal(p->left, target);
    	return left_size + p->cnt + GetRankByVal(p->right, target);
    }
    
    // 在以p为根的子树中查询排第rank名的元素
    int GetValByRank(Node* p, int rank) {
    	if (p == nullptr) return 1e9;
    	int left_size = p->left ? p->left->size : 0;
    	if (left_size >= rank) return GetValByRank(p->left, rank);
    	if (left_size + p->cnt >= rank) return p->key;
    	return GetValByRank(p->right, rank - left_size - p->cnt);
    }

    // 在以p为根的子树中插入data，返回新的根
    Node* Insert(Node* p, int data) {
        Node* res = p;  // 子树新的根
    	if (p == nullptr) {
    		res = new Node(data);
    	}
    	// 检索到重复，无需插入，副本数+1即可
    	else if (data == p->key) {
    		p->cnt++;
    	}
    	else if (data < p->key) {
    		p->left = Insert(p->left, data);
    		// 不满足堆性质，左孩子绕p右旋，左孩子代替p成为新的根
    		if (p->val < p->left->val) res = zig(p);
    	}
    	else {
    		p->right = Insert(p->right, data);
    		// 不满足堆性质，右孩子绕p左旋，右孩子代替p成为新的根
    		if (p->val < p->right->val) res = zag(p);
    	}
    	// 子树结构可能发生了变化，相应的信息需要一并更新
    	update(res);
    	return res;
    }

    // 在以p为根的子树中删除data，返回新的根
    Node* Remove(Node* p, int data) {
    	if (p == nullptr) return nullptr;  // data并不存在
    	if (data == p->key) {  // 检索到了val
    	    // 有重复，减少副本数即可
    		if (p->cnt > 1) {
    			p->cnt--;
    			update(p);
    			return p;
    		}
    		// 叶子节点，直接删除
    		if (!p->left && !p->right) {
    		    delete p;
    		    return nullptr;
    		}
    		// 不是叶子节点，向下旋转
    		Node* res = p;
    		// 左孩子权值更大，应该让左孩子绕p右旋，代替p的位置
			if (!p->right || (p->left && p->left->key > p->right->key)) {
				res = zig(p);
				res->right = Remove(res->right, data);
			}
			// 右孩子权值更大，应该让右孩子绕p左旋，代替p的位置
			else {
				res = zag(p);
				res->left = Remove(res->left, data);
			}
			if (res) update(res);
			return res;
    	}
    	if (data < p->key) p->left = Remove(p->left, data);
    	else p->right = Remove(p->right, data);
    	if (p) update(p);
    	return p;
    }

    // p的左孩子绕p向右旋转
    Node* zig(Node* p) {
    	Node* q = p->left;
    	p->left = q->right;
    	q->right = p;
    	update(p);
    	update(q);
    	return q;
    }
    
    // p的右孩子绕p向左旋转
    Node* zag(Node* p) {
        Node* q = p->right;
        p->right = q->left;
        q->left = p;
        update(p);
        update(q);
        return q;
    }

    // 更新结点p的附加信息（本题中是size）
    void update(Node* p) {
        int left_size = p->left ? p->left->size : 0;
        int right_size = p->right ? p->right->size : 0;
        p->size = left_size + right_size + p->cnt;
    }

    Node* root;
};

int main() {
	Treap treap;
	int n;
	cin >> n;
	while (n--) {
		int opt, x;
		scanf("%d%d", &opt, &x);
		switch (opt) {
		case 1:
			treap.Insert(x);
			break;
		case 2:
			treap.Remove(x);
			break;
		case 3:
			printf("%d\n", treap.GetRankByVal(x));
			break;
		case 4:
			printf("%d\n", treap.GetValByRank(x));
			break;
		case 5:
			printf("%d\n", treap.GetPre(x));
			break;
		case 6:
			printf("%d\n", treap.GetNext(x));
			break;
		}
	}
}
