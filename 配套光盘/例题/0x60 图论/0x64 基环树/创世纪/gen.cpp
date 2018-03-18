#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int mi = 19931117, N = 1000010;
int set[N], n;
inline void sinit (void) { for (int i = 1; i <= n; i++) set[i] = i; }
int sget (int a) { return set[a] == a ? a : (set[a] = sget(set[a])); }

int deg[N], pere[N], dp[N][2]; bool rec[N];
int head[N], val[N], nxt[N], mr;
typedef pair<int, int> pii;
vector<pii> ent;
int que[N], now, add;

inline void proc (int c)
{
    if (head[c] == -1) dp[c][0] = 0, dp[c][1] = -mi;
    else
    {
        dp[c][0] = 0, dp[c][1] = 1; bool zr = false;
        for (int p = head[c]; p != -1; p = nxt[p])
        {
            int t = val[p], rr = max(dp[t][0], dp[t][1]);
            if (dp[t][0] == rr) zr = true;
            dp[c][0] += rr, dp[c][1] += rr;
        }
        if (!zr)
        {
            int dlt = mi;
            for (int p = head[c]; p != -1; p = nxt[p])
            {
                int t = val[p];
                dlt = min(dlt, dp[t][1] - dp[t][0]);
            }
            dp[c][1] -= dlt;
        }
    }
}
int main ()
{
    freopen("gen.in", "r", stdin);
    freopen("gen.out", "w", stdout);
    scanf("%d", &n), sinit();
    memset(head, -1, sizeof head);
    for (int i = 1; i <= n; i++)
    {
        int x; scanf("%d", &x);
        if (sget(i) != sget(x))
        {
            pere[i] = x, set[sget(i)] = sget(x), ++deg[x];
            val[mr] = i, nxt[mr] = head[x]; head[x] = mr++;
        }
        else pere[i] = -1, ent.push_back(pii(i, x));
    }
    for (int i = 1; i <= n; i++) if (deg[i] == 0) que[add++] = i;
    while (now != add)
    {
        int c = que[now++];
        proc(c);
        if (pere[c] != -1)
        {
            --deg[pere[c]];
            if (deg[pere[c]] == 0) que[add++] = pere[c];
        }
    }
    int ans = 0;
    for (vector<pii>::iterator ite = ent.begin(); ite != ent.end(); ++ite)
    {
        int x = ite->first, y = ite->second;
        int add = dp[x][1], rc = 0;
        for (int p = head[y]; p != -1; p = nxt[p]) rc += dp[val[p]][1];
        if (dp[y][1] < rc + 1)
        {
            dp[y][1] = rc + 1; int cr = pere[y];
            while (cr != -1)
            {
                int t0 = dp[cr][0], t1 = dp[cr][1];
                proc(cr);
                if (t0 == dp[cr][0] && t1 == dp[cr][1]) break;
                else cr = pere[cr];
            }
        }
        add = max(add, dp[x][0]), ans += add;
    }
    printf("%d\n", ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
