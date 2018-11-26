//Author:XuHt
#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50006;
int n, ans[N];
struct COW {
	int id, l, r, ans;
	bool operator < (const COW x) const {
		return l < x.l;
	}
} cow[N];
priority_queue<pair<int, int> > s;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cow[i].id = i;
		scanf("%d %d", &cow[i].l, &cow[i].r);
	}
	sort(cow + 1, cow + n + 1);
	for (int i = 1; i <= n; i++) {
		int num = s.size();
		if (num && -s.top().first < cow[i].l) {
			cow[i].ans = s.top().second;
			s.pop();
			s.push(make_pair(-cow[i].r, cow[i].ans));
			continue;
		}
		cow[i].ans = ++num;
		s.push(make_pair(-cow[i].r, num));
	}
	cout << s.size() << endl;
	for (int i = 1; i <= n; i++) ans[cow[i].id] = cow[i].ans;
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
