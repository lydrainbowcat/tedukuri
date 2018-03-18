#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010, M = 500010;
int head[N], val[M], len[M], nxt[M], mr;
void ginit (int n)
{
    mr = 0;
    for (int i = 0; i < n; i++) head[i] = -1;
}
void glink (int a, int b, int v)
{
    val[mr] = b, len[mr] = v, nxt[mr] = head[a];
    head[a] = mr++;
}
const int mask = (1 << 22) - 1;
int dist[N], que[mask + 1], cnt[N];
bool inq[N];
bool spfa (int source, int n)
{
    int hd = mask + 1, tl = mask + 1; que[0] = source;
    for (int i = 0; i < n; i++) dist[i] = cnt[i] = 0;
    cnt[source] = 1, inq[source] = true;
    while (hd >= tl)
    {
        int cur = que[(hd--) & mask];
        inq[cur] = false;
        for (int p = head[cur]; p != -1; p = nxt[p])
        {
            int tar = val[p];
            if (dist[tar] < dist[cur] + len[p])
            {
                dist[tar] = dist[cur] + len[p];
                if (!inq[tar])
                {
                    if (dist[tar] >= dist[que[hd & mask]]) que[(++hd) & mask] = tar;
                    else que[(--tl) & mask] = tar;
                    inq[tar] = true;
                }
                ++cnt[tar];
                if (cnt[tar] >= n) return true;
            }
        }
    } return false;
}
int main ()
{
    freopen("gin.in", "r", stdin);
    freopen("gin.out", "w", stdout);
    int n, k; scanf("%d %d", &n, &k); ++n;
    ginit(n);
    for (int i = 0; i < k; i++)
    {
        int x, y, c; scanf("%d %d %d", &c, &x, &y);
        if (c == 1) glink(x, y, 0), glink(y, x, 0);
        else if (c == 2) glink(x, y, 1);
        else if (c == 3) glink(y, x, 0);
        else if (c == 4) glink(y, x, 1);
        else glink(x, y, 0);
    }
    for (int i = 1; i < n; i++) glink(0, i, 1);
    if (spfa(0, n)) printf("-1\n");
    else
    {
        __int64 ans = 0;
        for (int i = 1; i < n; i++) ans += dist[i];
        printf("%I64d\n", ans);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
