#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int N = 1250;

char map[N][N];
int col[N][N],row[N][N];
int link[N],head[N];
bool vis[N];
int cnt,n,m;
int R,C;

struct Edge
{
    int to;
    int next;
};

Edge edge[N*N];

void Init()
{
    cnt = 0;
    memset(head,-1,sizeof(head));
    memset(col,0,sizeof(col));
    memset(row,0,sizeof(row));
}

void add(int u,int v)
{
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

bool dfs(int u)
{
    for(int i=head[u]; ~i; i=edge[i].next)
    {
        int v = edge[i].to;
        if(!vis[v])
        {
            vis[v] = 1;
            if(link[v] == -1 || dfs(link[v]))
            {
                link[v] = u;
                return true;
            }
        }
    }
    return false;
}

int match()
{
    int ans = 0;
    memset(link,-1,sizeof(link));
    for(int i=1; i<=R; i++)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ans++;
    }
    return ans;
}

int main()
{
    int T,tt = 1;
    cin>>T;
    while(T--)
    {
        Init();
        cin>>n>>m;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                cin>>map[i][j];
        R = C = 1;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=m; j++)
            {
                if(map[i][j] != '#' && row[i][j] == 0)
                {
                    for(int k=j; map[i][k] != '#' && k <= m; k++)
                        row[i][k] = R;
                    ++R;
                }
                if(map[i][j] != '#' && col[i][j] == 0)
                {
                    for(int k=i; map[k][j] != '#' && k <= n; k++)
                        col[k][j] = C;
                    ++C;
                }
            }
        }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if(map[i][j] == 'o' && row[i][j] != 0 && col[i][j] != 0)
                    add(row[i][j],col[i][j]);
        printf("Case :%d\n",tt++);
        printf("%d\n",match());
    }
    return 0;
}

