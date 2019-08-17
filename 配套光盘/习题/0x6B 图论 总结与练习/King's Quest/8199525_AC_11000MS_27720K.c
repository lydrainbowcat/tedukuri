#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

typedef struct { int to, next; } graphnode;
graphnode graph[500010]; int grapmr, n;

void link (int a, int b)
{
    int p = grapmr++;
    graph[p].to = b, graph[p].next = graph[a].next;
    graph[a].next = p;
}

char instack[5100], sch[5100];
char lrc[5100][5100];
int stack[5100], top, scc[5100];
int dfn[5100], low[5100], sccidx, dfsidx;

void tarjan (int a)
{
    int p, tar;
    dfn[a] = low[a] = dfsidx++;
    stack[top++] = a;
    instack[a] = sch[a] = 1;
    for (p = graph[a].next; p != -1; p = graph[p].next)
    {
        tar = graph[p].to;
        if (sch[tar] == 0)
        {
            tarjan(tar);
            low[a] = min(low[a], low[tar]);
        }
        else if (instack[tar]) low[a] = min(low[a], dfn[tar]);
    }
    if (dfn[a] == low[a])
    {
        do
        {
            tar = stack[--top];
            scc[tar] = sccidx;
            instack[tar] = 0;
        } while (tar != a);
        sccidx++;
    }
}

int main ()
{
    int n, m, i, j, a, cnt;
    scanf("%d", &n);
    grapmr = n * 2;
    for (i = 0; i < grapmr; i++)
        graph[i].next = -1;
    memset(lrc, 0, sizeof(lrc));
    for (i = 0; i < n; i++)
    {
        scanf("%d", &m);
        for (j = 0; j < m; j++)
        {
            scanf("%d", &a);
            link(i, a + n - 1);
            lrc[i][a - 1] = 1;
        }
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a);
        link(a + n - 1, i);
    }
    memset(sch, 0, sizeof(sch));
    memset(instack, 0, sizeof(instack));
    dfsidx = sccidx = top = 0;
    for (i = 0; i < n * 2; i++)
        if (sch[i] == 0) tarjan(i);
    for (i = 0; i < n; i++)
    {
        cnt = 0;
        for (j = n; j < n * 2; j++)
            if (scc[i] == scc[j] && lrc[i][j - n]) cnt++;
        printf("%d ", cnt);
        for (j = n; j < n * 2; j++)
            if (scc[i] == scc[j] && lrc[i][j - n]) printf("%d ", j - n + 1);
        printf("\n");
    }
    //system("pause");
    return 0;
}
