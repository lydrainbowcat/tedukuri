//Author:XuHt
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 66;
int n, k, s, tot, id[16][16], dep, tmp;
vector<int> e[N], g[N];
bool v[N];

int gj() {
	bool w[N];
	memcpy(w, v, sizeof(w));
	int ans = 0;
	for (int i = 1; i <= tot; i++)
		if (w[i]) {
			if (!ans) tmp = i;
			++ans;
			for (unsigned int j = 0; j < g[i].size(); j++)
				for (unsigned int x = 0; x < e[g[i][j]].size(); x++)
					w[e[g[i][j]][x]] = 0;
		}
	return ans;
}

bool dfs(int now) {
	int cnt = gj();
	if (!cnt) return 1;
	if (now + cnt > dep) return 0;
	bool w[N];
	memcpy(w, v, sizeof(w));
	int tmp0 = tmp;
	for (unsigned int i = 0; i < g[tmp0].size(); i++) {
		int st = g[tmp0][i];
		for (unsigned int j = 0; j < e[st].size(); j++)
			v[e[st][j]] = 0;
		if (dfs(now + 1)) return 1;
		memcpy(v, w, sizeof(v));
	}
	return 0;
}

void Square_Destroyer() {
	cin >> n >> k;
	s = 2 * n + 1;
	tot = 0;
	for (int i = 1; i <= s; i++)
		for (int j = 1; j <= s; j++)
			if ((i & 1) != (j & 1)) id[i][j] = ++tot;
	for (int i = 1; i <= tot; i++) e[i].clear();
	int z = n * (n + 1) * (2 * n + 1) / 6;
	for (int i = 1; i <= z; i++) g[i].clear();
	tot = 0;
	for (int a = 1; a < s; a += 2)
		for (int i = 2; i + a <= s; i += 2)
			for (int j = 2; j + a <= s; j += 2) {
				++tot;
				for (int x = 0; x < a; x += 2) {
					e[id[x+i][j-1]].push_back(tot);
					e[id[x+i][j+a]].push_back(tot);
					e[id[i-1][x+j]].push_back(tot);
					e[id[i+a][x+j]].push_back(tot);
					g[tot].push_back(id[x+i][j-1]);
					g[tot].push_back(id[x+i][j+a]);
					g[tot].push_back(id[i-1][x+j]);
					g[tot].push_back(id[i+a][x+j]);
				}
			}
	memset(v, 1, sizeof(v));
	for (int i = 1; i <= k; i++) {
		int a;
		cin >> a;
		for (unsigned int j = 0; j < e[a].size(); j++)
			v[e[a][j]] = 0;
	}
	dep = 0;
	while (!dfs(0)) ++dep;
	cout << dep << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) Square_Destroyer();
	return 0;
}
