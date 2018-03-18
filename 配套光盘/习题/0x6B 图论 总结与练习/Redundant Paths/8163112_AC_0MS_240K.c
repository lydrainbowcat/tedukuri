#include <stdio.h>
#include <stdlib.h>
#define min(a,b) ((a)<(b)?(a):(b))

typedef struct { int to, next; } graphnode;
graphnode graph[30010]; int grapmr;

void link (int a, int b)
{
    int p = grapmr++;
    graph[p].to = b, graph[p].next = graph[a].next;
    graph[a].next = p;
}

int low[5010], dfn[5010], bcc[5010];
int dfsidx, bccidx, stack[5010], top;
int deg[5010];

typedef struct { int x, y; } side;
side memory[10010]; int memmr;

int comp (const void *a, const void *b)
{
    side *sa = (side *)a, *sb = (side *)b;
    if (sa->x != sb->x) return sa->x - sb->x;
    else return sa->y - sb->y;
}

void tarjan (int idx, int pere)
{
    int p, tar, t;
    dfn[idx] = low[idx] = dfsidx++;
    stack[top++] = idx;
    for (p = graph[idx].next; p != -1; p = graph[p].next)
    {
        tar = graph[p].to;
        if (tar == pere) continue;
        else if (dfn[tar] == -1)
        {
            tarjan(tar, idx);
            low[idx] = min(low[idx], low[tar]);
            if (low[tar] > dfn[idx])
            {
                memory[memmr].x = idx, memory[memmr].y = tar;
                memmr++;
                do
                {
                    t = stack[--top];
                    bcc[t] = bccidx;
                } while (t != tar);
                bccidx++;
            }
        }
        else low[idx] = min(low[idx], dfn[tar]);
    } 
}

int main ()
{
    int n, m, i, a, b, r;
    scanf("%d %d", &n, &m);
    grapmr = n;
    for (i = 0; i < n; i++)
        graph[i].next = -1;
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &b);
        memory[i].x = a - 1, memory[i].y = b - 1;
    }
    qsort(memory, m, sizeof(side), comp);
    for (i = 0; i < m; i++)
    {
        if (i > 0 && memory[i].x == memory[i - 1].x && memory[i].y == memory[i - 1].y) continue;
        a = memory[i].x, b = memory[i].y;
        link(a, b);
        link(b, a);
    }
    memset(dfn, -1, sizeof(dfn));
    memset(deg, 0, sizeof(deg));
    dfsidx = top = memmr = 0;
    bccidx = 1;
    tarjan(0, -1);
    for (i = 0; i < memmr; i++)
    {
        a = bcc[memory[i].x];
        b = bcc[memory[i].y];
        deg[a]++, deg[b]++;
    }
    for (r = 0, i = 0; i < bccidx; i++)
        if (deg[i] == 1) r++;
    printf("%d\n", (r + 1) / 2);
    return 0;
} 
