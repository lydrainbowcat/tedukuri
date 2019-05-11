#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct rec {
	int a, b; // 两个变量，其中a>=b
	int val, cnt; // 未来估价val，当前次数cnt
	rec() {}
	rec(int a_, int b_, int val_, int cnt_) {
		a = a_, b = b_, val = val_, cnt = cnt_;
	}
};
int n;
const int N = 1000000, mod = 999983;
priority_queue<rec> q;
pair<int, int> ver[N];
int head[N], d[N], nxt[N], tot; // 手动hash

inline bool operator <(const rec &a, const rec &b) {
	return a.val + a.cnt > b.val + b.cnt;
}

// 估价函数，把a不断自加直至>=n所需的次数（注意a>=b），显然实际所需次数不会小于这一次数
inline int calc(int a, int b) {
	int val = 0;
	for (; a < n; a *= 2) val++;
	return val;
}

inline int gcd(int a, int b) {
	return b ? gcd(b, a%b) : a;
}

inline bool get_or_update(int a, int b, int cnt) {
	int hash = (long long)a * b % mod;
	for (int i = head[hash]; i; i = nxt[i]) {
		if (ver[i].first == a && ver[i].second == b) {
			if (d[i] > cnt) {
				d[i] = cnt;
				return true;
			}
			return false;
		}
	}
	d[++tot] = cnt;
	ver[tot] = make_pair(a, b);
	nxt[tot] = head[hash], head[hash] = tot;
	return true;
}

inline void insert(int a, int b, int cnt) {
	if (a < b) swap(a, b); // 保证a>=b
	if (n % gcd(a, b)) return; // 剪枝
	bool updated = get_or_update(a, b, cnt);
	if (updated) q.push(rec(a, b, calc(a, b), cnt));
}

int astar() {
	insert(1, 0, 0);
	while (q.size()) {
		rec now = q.top();
		q.pop();
		if (now.a == n || now.b == n) return now.cnt; // 第一次取出答案
		insert(now.a * 2, now.b, now.cnt + 1);
		insert(now.a, now.b * 2, now.cnt + 1);
		if (now.a) insert(now.a * 2, now.a, now.cnt + 1);
		if (now.b) insert(now.b * 2, now.b, now.cnt + 1);
		if (now.a - now.b >= 0) insert(now.a - now.b, now.a, now.cnt + 1), insert(now.a - now.b, now.b, now.cnt + 1);
		if (now.b - now.a >= 0) insert(now.b - now.a, now.a, now.cnt + 1), insert(now.b - now.a, now.b, now.cnt + 1);
		insert(now.a + now.b, now.b, now.cnt + 1);
		insert(now.a + now.b, now.a, now.cnt + 1);
	}
}

int main() {
	cin >> n;
	cout << astar() << endl;
}