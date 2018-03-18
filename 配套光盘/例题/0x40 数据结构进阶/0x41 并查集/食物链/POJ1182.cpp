#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int fa[200000];
int n,m,k,x,y,ans;

int get(int x)
{
    if(x==fa[x]) return x;
    return fa[x]=get(fa[x]);
}

void ver(int x,int y)
{
    fa[get(x)]=get(y);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=3*n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&k,&x,&y);
        if(x>n||y>n) ans++;
        else if(k==1)
        {
            if(get(x)==get(y+n)||get(x)==get(y+n+n)) ans++;
            else{
                ver(x,y);
                ver(x+n,y+n);
                ver(x+n+n,y+n+n);
            }
        }
        else{
            if(x==y||get(x)==get(y)||get(x)==get(y+n)) ans++;
            else{
                ver(x,y+n+n);
                ver(x+n,y);
                ver(x+n+n,y+n);
            }
        }
    }
    cout<<ans<<endl;
}