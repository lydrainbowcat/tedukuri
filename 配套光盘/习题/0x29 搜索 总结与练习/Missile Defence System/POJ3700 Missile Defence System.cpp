//Author:XuHt
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
const int N = 56;
int n, a[N];
unsigned int dep;
vector<int> up, down;

bool dfs(int x) {
	if (up.size() + down.size() > dep) return 0;
	if (x == n + 1) return 1;
	int num = 0, t;
	for (unsigned int i = 0; i < up.size(); i++)
		if (up[i] < a[x] && up[i] > num) {
			num = up[i];
			t = i;
		}
	if (num) {
		up[t] = a[x];
		if (dfs(x + 1)) return 1;
		up[t] = num;
	} else {
		up.push_back(a[x]);
		if (dfs(x + 1)) return 1;
		up.pop_back();
	}
	num = 0x3f3f3f3f;
	for (unsigned int i = 0; i < down.size(); i++)
		if (down[i] > a[x] && down[i] < num) {
			num = down[i];
			t = i;
		}
	if (num != 0x3f3f3f3f) {
		down[t] = a[x];
		if (dfs(x + 1)) return 1;
		down[t] = num;
	} else {
		down.push_back(a[x]);
		if (dfs(x + 1)) return 1;
		down.pop_back();
	}
	return 0;
}

void Missile_Defence_System() {
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	up.clear();
	down.clear();
	dep = 0;
	while (!dfs(1)) ++dep;
	cout << dep << endl;
}

int main() {
	while (cin >> n && n) Missile_Defence_System();
	return 0;
}
