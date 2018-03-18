#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

#define inf 0x3f3f3f3f
#define Max 110

struct node
{
    int l,r,co;
    int mid()
    {
        return (l+r)>>1;
    }
}T[4*200010];

int l[50100],r[50100];
int dp[50100][2],ans;
int rec;

void build(int l,int r,int rt)
{
    T[rt].l=l;T[rt].r=r;T[rt].co=-1;
    if(l==r)
    {
        T[rt].co=0;
        return;
    }
    int mid=T[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
}

void down(int rt)
{
    if(T[rt].l==T[rt].r||T[rt].co==-1)
        return;
    T[rt<<1].co=T[rt].co;
    T[rt<<1|1].co=T[rt].co;
    T[rt].co=-1;
}

void modify(int l,int r,int rt,int co)
{
    if(T[rt].l==l&&T[rt].r==r)
    {
        T[rt].co=co;
        return;
    }
    down(rt);//lazy
    int mid=T[rt].mid();
    if(r<=mid)
        modify(l,r,rt<<1,co);
    else if(l>=mid+1)
        modify(l,r,rt<<1|1,co);
    else
    {
        modify(l,mid,rt<<1,co);
        modify(mid+1,r,rt<<1|1,co);
    }
}

void query(int x,int rt)
{
    if(T[rt].l==T[rt].r)
    {
        rec=T[rt].co;
        return;
    }
    down(rt);
    int mid=T[rt].mid();
    if(x<=mid)
        query(x,rt<<1);
    else
        query(x,rt<<1|1);
}

int main()
{
    int n,s,i;
    scanf("%d%d",&n,&s);
    build(0,200000,1);
    l[0]=r[0]=100000;
    s+=100000;
    dp[0][0]=0;
    dp[0][1]=0;
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&l[i],&r[i]);
        l[i]+=100000;r[i]+=100000;
        query(l[i],1);
        dp[i][0]=min(dp[rec][0]+abs(l[i]-l[rec]),dp[rec][1]+abs(r[rec]-l[i]));
        query(r[i],1);
        dp[i][1]=min(dp[rec][0]+abs(r[i]-l[rec]),dp[rec][1]+abs(r[rec]-r[i]));
        modify(l[i],r[i],1,i);
    }
    ans=min(dp[n][0]+s-l[n],dp[n][1]+r[n]-s);
    printf("%d\n",ans);
    return 0;
}