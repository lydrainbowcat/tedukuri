#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct graphnode { int to, next; } graph[500010]; int grapmr;
vector<int> attach[100010];
int n, m, pwr[100010], ans;
inline void ginit (void)
{
    grapmr = n;
    for (int i = 0; i < n; i++) graph[i].next = -1, attach[i].clear();
}
inline void glink (int a, int b)
{
    int p = grapmr++;
    graph[p].to = b, graph[p].next = graph[a].next;
    graph[a].next = p;
}
int set[100010]; bool sch[100010];
inline void sinit (void) { for (int i = 0; i < n; i++) set[i] = i; }
int sget (int a) { return set[a] == a ? a : (set[a] = sget(set[a])); }
void satt (int a, int to) { set[sget(a)] = sget(to); }
void lca_tarjan (int x, int pere)
{
    for (vector<int>::iterator ite = attach[x].begin(); ite != attach[x].end(); ++ite)
    {
        int tar = (*ite);
        if (sch[tar])
        {
            int lca = sget(tar);
            ++pwr[x], ++pwr[tar], pwr[lca] -= 2;
        }
    }
    sch[x] = true;
    for (int p = graph[x].next; p != -1; p = graph[p].next)
    {
        int tar = graph[p].to;
        if (tar == pere) continue;
        lca_tarjan(tar, x);
    }
    if (pere != -1) satt(x, pere);
}
void stat (int x, int pere)
{
    for (int p = graph[x].next; p != -1; p = graph[p].next)
    {
        int tar = graph[p].to;
        if (tar == pere) continue;
        stat(tar, x);
        pwr[x] += pwr[tar];
    }
    if (pere != -1)
    {
        if (pwr[x] == 0) ans += m;
        else if (pwr[x] == 1) ans += 1;
    }
}
int main ()
{
    scanf("%d %d", &n, &m), ginit();
    for (int i = 0; i < n - 1; i++)
    {
        int a, b; scanf("%d %d", &a, &b); --a, --b;
        glink(a, b), glink(b, a);
    }
    for (int i = 0; i < m; i++)
    {
        int a, b; scanf("%d %d", &a, &b); --a, --b;
        if (a != b) attach[a].push_back(b), attach[b].push_back(a);
    }
    sinit(), memset(sch, false, sizeof sch);
    memset(pwr, 0, sizeof pwr);
    lca_tarjan(0, -1);
    ans = 0, stat(0, -1);
    printf("%d\n", ans);
    return 0;
}
