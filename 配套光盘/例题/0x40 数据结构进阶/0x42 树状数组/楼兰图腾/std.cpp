#include<stdio.h>
#include<stdlib.h>
const int maxn=2000000;
int left[maxn],right[maxn],sum[maxn];
int i,j,n;
long long ans1,ans2;

void build(int l,int r,int c)
{
    int mid=(l+r)/2;
    left[c]=l;
    right[c]=r;
    sum[c]=0;
    if (l!=r)
    {
        build(l,mid,c*2);
        build(mid+1,r,c*2+1);
    }
}

void insert(int x,int c)
{
    int mid=(left[c]+right[c])/2;
    if (left[c]==right[c])
    {
        sum[c]=1;
        return;
    }
    if (x<=mid) insert(x,c*2);
    if (x>=mid+1) insert(x,c*2+1);
    sum[c]=sum[c*2]+sum[c*2+1];
}

int answer(int l,int r,int c)
{
    if (l>r) return 0;
    int mid=(left[c]+right[c])/2;
    if ((l==left[c])&&(r==right[c]))
         return sum[c];
    if (r<=mid) return answer(l,r,c*2);
    if (l>=mid+1) return answer(l,r,c*2+1);
    return answer(l,mid,c*2)+answer(mid+1,r,c*2+1);
}

int main()
{
    scanf("%d",&n);
    build(1,n,1);
    for (i=1;i<=n;i++)
    {
        int y;
        scanf("%d",&y);
        insert(y,1);
        ans1+=(long long)answer(y+1,n,1)*(n-y-answer(y+1,n,1));
        ans2+=(long long)answer(1,y-1,1)*(y-1-answer(1,y-1,1));
    }
    printf("%lld %lld\n",ans1,ans2);
    return 0;
}

