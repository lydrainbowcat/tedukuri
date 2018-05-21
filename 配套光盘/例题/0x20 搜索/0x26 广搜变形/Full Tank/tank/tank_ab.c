/* Sample solution for the Full Tank? problem in NCPC'07 by Andreas Björklund */
#include <stdio.h>

#define MAXN (1000)
#define MAXM (10000)
#define MAXC (101)
#define HUGE (1e8)

struct ted
{
  int d,w;
};

int n,m,c;
int nbrE[MAXN];
struct ted edge[MAXN][MAXN];

int cost[MAXN][MAXC];
int p[MAXN];
int vis[MAXN][MAXC];

struct thp
{
  int u,c,d;
};

int nheap;
struct thp heap[MAXN*MAXC];
int map[MAXN][MAXC];

void swap(int a,int b)
{
  struct thp tmp;
  tmp=heap[a];
  heap[a]=heap[b];
  heap[b]=tmp;
  map[heap[a].u][heap[a].c]=a;
  map[heap[b].u][heap[b].c]=b;
}
     
void addRoot(int who)
{
  if (who*2<=nheap)
  {
    int val=heap[who*2-1].d;
    if (who*2+1<=nheap && heap[who*2].d<val && heap[who*2].d<heap[who-1].d)
    {
      swap(who-1,who*2);
      addRoot(2*who+1);
    }
    else if (heap[who*2-1].d<heap[who-1].d)
    {
      swap(who-1,who*2-1);
      addRoot(2*who);
    }  
  }
}

void addLeaf(int who)
{
  if (who>1)
  {
    int val=heap[who/2-1].d;
    if (heap[who-1].d<val)
    {
      swap(who-1,who/2-1);
      addLeaf(who/2);
    }
  }
}

void deq(int *u,int *cap)
{
  if (!nheap)
    *u=-1;
  else
  {
    *u=heap[0].u;
    *cap=heap[0].c;  
    heap[0]=heap[--nheap];
    addRoot(1);
  }
}

void enq(int u,int cap)
{
  if (map[u][cap]==-1)
  {
    heap[nheap].u=u;
    heap[nheap].c=cap;
    heap[nheap].d=cost[u][cap];
    map[u][cap]=nheap;
    nheap++;
    addLeaf(nheap);    
  }
  else
  {
    heap[map[u][cap]].d=cost[u][cap];
    addLeaf(map[u][cap]+1);
  }
}

void addEdge(int u,int v,int d)
{
  edge[u][nbrE[u]].d=d;
  edge[u][nbrE[u]++].w=v;
  edge[v][nbrE[v]].d=d;
  edge[v][nbrE[v]++].w=u;
}

int main(void)
{
  int i,j,k,u,v,d,q,cap;
  scanf("%d %d",&n,&m);
  for (i=0;i<n;i++)
  {
    nbrE[i]=0;
    scanf("%d",&p[i]);
  }
  
  for (i=0;i<m;i++)
  {
    scanf("%d %d %d",&u,&v,&d);
    addEdge(u,v,d);
  } 

  scanf("%d",&q);
  for (k=0;k<q;k++)
  {
    scanf("%d %d %d",&c,&u,&v);
   
    for (i=0;i<=c;i++)
      for (j=0;j<n;j++)
      {
        cost[j][i]=HUGE;
        map[j][i]=-1;
      }
    
    cost[u][0]=0;
    nheap=0;
    
    for (i=0;i<n;i++)
      for (j=0;j<=c;j++)
         vis[i][j]=0;
    
    cap=0;  
    while (!(u==v && cap==0) && u!=-1)
    {
      vis[u][cap]=1;
      if (cap<c && !vis[u][cap+1])
        if (cost[u][cap]+p[u]<cost[u][cap+1])
        {
          cost[u][cap+1]=cost[u][cap]+p[u];
          enq(u,cap+1);
        }
      
      for (i=0;i<nbrE[u];i++)
      {
        int d=edge[u][i].d;
        int w=edge[u][i].w;    
        if (d<=cap && !vis[w][cap-d])
          if (cost[w][cap-d]>cost[u][cap])
          {
            cost[w][cap-d]=cost[u][cap];
            enq(w,cap-d);
          }
      }
      deq(&u,&cap);
    }  
    if (cost[v][0]==HUGE || u==-1) printf("impossible\n"); else printf("%d\n",cost[v][0]);
  }
  return 0;
}
