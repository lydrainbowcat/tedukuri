#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue> 
using namespace std;
const int mod = 1000000007;
int n, m, s, t, Q;
int ver[2 * 200005], edge[2 * 200005], nxt[2 * 200005], head[100005], tot;
int in[100005], out[100005], fs[100005], ft[100005], d[100005], pre[100005];
bool bridge[2 * 200005];
int a[100005], sum[100005], danger[100005], dps[100005], dpt[100005];
queue<int> q;

void add(int x, int y, int z) {
	ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

void topsort(int s, int in[100005], int rev, int f[100005]) {
	f[s] = 1;
	for (int i = 1; i <= n; i++)
		if (in[i] == 0) q.push(i);
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			if ((i & 1) != rev) continue;
			int y = ver[i];
			f[y] = (f[y] + f[x]) % mod;
			if (--in[y] == 0) q.push(y);
			if (rev == 0 && d[y] > d[x] + edge[i]) {
				d[y] = d[x] + edge[i];
				pre[y] = i;
			}
		}
	}
}

int main() {
	int T; cin >> T;
	while (T--) {
		cin >> n >> m >> s >> t >> Q;
		s++, t++;
		memset(head, 0, sizeof(head));
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		memset(fs, 0, sizeof(fs));
		memset(ft, 0, sizeof(ft));
		memset(bridge, 0, sizeof(bridge));
		memset(d, 0x3f, sizeof(d));
		tot = 1; d[s] = 0;
		for (int i = 1; i <= m; i++) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			x++, y++;
			add(x, y, z), in[y]++; // 下标为2,4,6,...的为正向图
			add(y, x, z), out[x]++; // 下标为3,5,7,...的为反图
		}
		// 在正向图上拓扑排序求s到每个点的路径条数，同时求出最短路
		topsort(s, in, 0, fs);
		if (fs[t] == 0) { puts("-1"); continue; }
		// 在反向图上拓扑排序求每个点到t的路径条数
		topsort(t, out, 1, ft);
		// 求出桥边
		for (int i = 2; i <= tot; i += 2) {
			int x = ver[i ^ 1], y = ver[i];
			if ((long long)fs[x] * ft[y] % mod == fs[t]) bridge[i] = 1;
		}
		int p = 0;
		for (int x = t; x != s; x = ver[pre[x] ^ 1]) {
			a[++p] = pre[x];
			sum[p] = sum[p - 1] + edge[a[p]];
			danger[p] = danger[p - 1] + (bridge[a[p]] ? edge[a[p]] : 0);
		}
		dps[0] = dpt[p + 1] = 0;
		for (int i = 1, j = 0; i <= p; i++) {
			while (sum[i] - sum[j] > Q) j++;
			// 前i-1段搭1次车，第i段步行，或者前j段步行，第j+1~i段搭车
			int z = bridge[a[i]] ? edge[a[i]] : 0;
			int side = j > 0 && bridge[a[j]] ? Q - (sum[i] - sum[j]) : 0;
			dps[i] = min(dps[i - 1] + z, danger[j] - side);
		}
		for (int i = p, j = p; i; i--) {
			while (sum[j] - sum[i - 1] > Q) j--;
			// 第i+1~p段搭1次车，第i段步行，或者第j+1~p段步行，第i~j段搭车
			int z = bridge[a[i]] ? edge[a[i]] : 0;
			int side = j < p && bridge[a[j + 1]] ? Q - (sum[j] - sum[i - 1]) : 0;
			dpt[i] = min(dpt[i + 1] + z, danger[p] - danger[j] - side);
		}
		int ans = 1 << 30;
		for (int i = 1; i <= p; i++) ans = min(ans, dps[i - 1] + dpt[i]);
		cout << ans << endl;
	}
}