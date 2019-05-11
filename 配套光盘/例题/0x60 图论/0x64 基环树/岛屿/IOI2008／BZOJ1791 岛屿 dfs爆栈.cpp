//Author:XuHt
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1000006;
int Head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], tot = 1;
int n, top, inst[N], q[N];
ll ans, d[N], f[N];
pair<int, ll> st[N];
vector<pair<int, ll> > s;
bool vis[N<<1], v[N], ins[N], w[N];

inline void add(int x, int y, int z) {
    Edge[++tot] = y;
    Leng[tot] = z;
    Next[tot] = Head[x];
    Head[x] = tot;
}

void dfs(int x) {
    for (int i = Head[x]; i; i = Next[i]) {
        int y = Edge[i];
        ll z = Leng[i];
        if (v[y]) {
            if (!vis[i^1]) {
                for (int j = inst[y] + 1; j <= top; j++) {
                    s.push_back(st[j]);
                    ins[st[j].first] = 1;
                }
                s.push_back(make_pair(y, z));
                ins[y] = vis[i] = 1;
            }
            continue;
        }
        v[y] = vis[i] = 1;
        st[++top] = make_pair(y, z);
        inst[y] = top;
        dfs(y);
        --top;
    }
}

void dp(int x, ll &now) {
    w[x] = 1;
    for (int i = Head[x]; i; i = Next[i]) {
        int y = Edge[i];
        if (w[y] || ins[y]) continue;
        dp(y, now);
        ll z = Leng[i];
        now = max(now, d[x] + d[y] + z);
        d[x] = max(d[x], d[y] + z);
    }
}

int main() {
    cin >> n;
    for (int x = 1; x <= n; x++) {
        int y, z;
        scanf("%d %d", &y, &z);
        add(x, y, z);
        add(y, x, z);
    }
    for (int i = 1; i <= n; i++)
        if (!v[i]) {
            s.clear();
            v[i] = 1;
            st[1] = make_pair(i, 0);
            inst[i] = top = 1;
            dfs(i);
            ll now = 0;
            for (unsigned int i = 0; i < s.size(); i++)
                dp(s[i].first, now);
            int sz = s.size();
            for (int i = 0; i < sz; i++)
                s.push_back(s[i]);
            int l = 0, r = 1;
            q[0] = 0;
            for (unsigned int i = 1; i < s.size(); i++) {
                f[i] = f[i-1] + s[i].second;
                ll val = d[s[i].first] - f[i];
                if (l < r && q[r-1] - q[l] >= sz - 1) ++l;
                now = max(now, f[i] + d[s[i].first] + d[s[q[l]].first] - f[q[l]]);
                while (l < r && d[s[q[r-1]].first] - f[q[r-1]] <= val) --r;
                q[r++] = i;
            }
            ans += now;
        }
    cout << ans << endl;
    return 0;
}
