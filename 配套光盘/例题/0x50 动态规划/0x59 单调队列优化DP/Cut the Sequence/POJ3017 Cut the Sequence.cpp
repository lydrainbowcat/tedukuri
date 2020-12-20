#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;
int n, a[100010], c[100010], q[100010];
long long m, f[100010];
// 在队列q[j]和平衡树存储的f[q[j]]+a[q[j+1]]之间建立映射关系
multiset<long long> s;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if (a[i] > m) {
			puts("-1");
			return 0;
		}
	}
	long long sum = 0;
	for (int i = 1, j = 0; i <= n; i++) {
		sum += a[i];
		while (sum > m) sum -= a[j + 1], j++;
		c[i] = j;
	}
	int l = 1, r = 0;
	for (int i = 1; i <= n; i++) {
		while (l <= r && q[l] <= c[i]) {
			s.erase(f[q[l]] + a[q[l + 1]]);
			l++;
		}
		while (l <= r && a[q[r]] <= a[i]) {
			// 删除队尾时，队尾之前(r-1位置)的f[...]+a[...]这个值发生了变化
			// 所以要把旧的值删掉，在插入i时再加回去
			s.erase(f[q[r - 1]] + a[q[r]]);
			r--;
		}
		if (l <= r) s.insert(f[q[r]] + a[i]);
		q[++r] = i;
		f[i] = f[c[i]] + a[q[l]];
		if (!s.empty()) f[i] = min(f[i], *s.begin());
	}
	cout << f[n] << endl;
}