#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

inline int min (int a, int b) { if (a < b) return a; else return b; }
inline int max (int a, int b) { if (a > b) return a; else return b; }

class graph
{
private:
    int mr;
public:
    struct { int to, next; } arr[20010];
    void initialize (int n);
    void link (int a, int b);
} gra, maz;
void graph::initialize (int n)
{
    mr = n;
    for (int i = 0; i < n; i++)
        arr[i].next = -1;
}
void graph::link (int a, int b)
{
    int p = mr++;
    arr[p].to = b, arr[p].next = arr[a].next;
    arr[a].next = p;
}

int dfsidx, dfn[1010], low[1010];
int stack[1010], top;
bool sch[1010], instack[1010];
int sccidx, scc[1010];

void tarjan (int x)
{
    int p, tar;
    dfn[x] = low[x] = dfsidx++;
    sch[x] = instack[x] = true;
    stack[top++] = x;
    for (p = gra.arr[x].next; p != -1; p = gra.arr[p].next)
    {
        tar = gra.arr[p].to;
        if (sch[tar] == false)
        {
            tarjan(tar);
            low[x] = min(low[x], low[tar]);
        }
        else if (instack[tar]) low[x] = min(low[x], dfn[tar]);
    }
    if (low[x] == dfn[x])
    {
        do
        {
            tar = stack[--top];
            instack[tar] = false;
            scc[tar] = sccidx;
        } while (tar != x);
        sccidx++;
    }
}

int deg[1010], queue[1010], dyna[1010], now, add;
pair <int, int> list[10010];

int main ()
{
    int kase, n, m, a, b, p, tar, cur, maxc; bool ans;
    scanf("%d", &kase);
    for (; kase > 0; kase--)
    {
        scanf("%d %d", &n, &m);
        gra.initialize(n); ans = true;
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d", &a, &b); a--, b--;
            list[i].first = a, list[i].second = b;
            gra.link(a, b);
        }
        memset(sch, 0, sizeof(sch));
        memset(instack, 0, sizeof(instack));
        top = dfsidx = sccidx = 0;
        for (int i = 0; i < n; i++)
            if (sch[i] == false) tarjan(i);
        maz.initialize(sccidx);
        memset(deg, 0, sizeof(deg));
        memset(dyna, 0, sizeof(dyna));
        for (int i = 0; i < m; i++)
        {
            a = list[i].first;
            b = list[i].second;
            if (scc[a] != scc[b])
            {
                maz.link(scc[a], scc[b]);
                deg[scc[b]]++;
            }
        }
        now = add = maxc = 0;
        for (int i = 0; i < sccidx; i++)
        {
            if (deg[i] == 0)
            {
                queue[add++] = i;
                dyna[i] = 1;
            }
        }
        while (now != add)
        {
            cur = queue[now++];
            maxc = max(maxc, dyna[cur]);
            for (p = maz.arr[cur].next; p != -1; p = maz.arr[p].next)
            {
                tar = maz.arr[p].to;
                dyna[tar] = max(dyna[tar], dyna[cur] + 1);
                deg[tar]--;
                if (deg[tar] == 0) queue[add++] = tar;
            }
        }
        if (maxc < sccidx) ans = false;
        if (ans) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
