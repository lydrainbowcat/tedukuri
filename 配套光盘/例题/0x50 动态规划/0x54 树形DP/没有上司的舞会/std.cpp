#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> son[10010];
int f[10010][2], v[10010], h[10010], n;

void dp(int x) {
    f[x][0] = 0;
	f[x][1] = h[x];
	for (int i = 0; i < son[x].size(); i++) {
		int y = son[x][i];
		dp(y);
		f[x][0] += max(f[y][0], f[y][1]);
		f[x][1] += f[y][0];
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		v[x] = 1; // x has a father
		son[y].push_back(x); // x is a son of y
	}
	int root;
	for (int i = 1; i <= n; i++)
		if (!v[i]) { // i doesn't have a father
            root = i;
            break;
        }
	dp(root);
	cout << max(f[root][0], f[root][1]) << endl;
}