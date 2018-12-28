/*
跟随一个上升的拦截系统
跟随一个下降的拦截系统
（不能跟随）新建一个 

对于拦截系统   (末尾高度，上升/下降/都可以) 
                            0   1   2*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std; 
int f[100][2];
int a[100], n, m, ans;

//迭代加深DFS（ID-DFS）
bool dfs(int idx) { 
	if (m > ans) return false; // 深度限制 
	if (idx > n) {
		return true;
	}
	bool flag_up = 0, flag_down = 0;
	// 跟上升
	int h = 0, choice = 0;
	for (int i = 1; i <= m; i++) { // 找高度<=a[idx]的最大的一个 
		int tail = f[i][0];
		int state = f[i][1];
		if (a[idx] >= tail && state == 0 && tail > h) {
			h = tail;
			choice = i;
		}
	}
	if (choice) { // 能跟随上升 
		f[choice][0] = a[idx];
		if (dfs(idx + 1)) return true;
		f[choice][0] = h;
		flag_up = 1;
	}
	// 跟下降
	h = 1e9, choice = 0;
	for (int i = 1; i <= m; i++) { // 找高度>=a[idx]的最小的一个 
		int tail = f[i][0];
		int state = f[i][1];
		if (a[idx] <= tail && state == 1 && tail < h) {
			h = tail;
			choice = i;
		}
	}
	if (choice) { // 能跟随下降 
		f[choice][0] = a[idx];
		if (dfs(idx + 1)) return true;
		f[choice][0] = h;
		flag_down = 1;
	}
	if (!flag_up) { // 新建上升 
		m++;
		f[m][0] = a[idx];
		f[m][1] = 0;
		if (dfs(idx + 1)) return true;
		m--;
	}
	if (!flag_down) { // 新建下降 
	    m++;
		f[m][0] = a[idx];
		f[m][1] = 1;
		if (dfs(idx + 1)) return true;
		m--;
	}
	return false;
} 

int main() {
	while(cin >> n && n) {
		for (int i = 1; i <= n; i++) cin >> a[i];
			// a[i] = rand() % 100 + 1;
		ans = 1;
		while (true) { // 迭代加深 
			m = 0;
			if (dfs(1)) break;
			ans++;
		}
		cout << ans << endl;
	}
}