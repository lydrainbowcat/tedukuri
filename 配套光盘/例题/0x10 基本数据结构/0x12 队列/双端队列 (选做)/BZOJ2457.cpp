#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#define MAXN 200100
using namespace std;
struct node{
    int v,ps;
}a[MAXN*2];
int n;
int mx[MAXN],mi[MAXN],cnt=0;
int ans=0,flag=1,now=1<<30;
 
bool cmp(const node A,const node B){return A.v<B.v||(A.v==B.v&&A.ps<B.ps);}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i].v),a[i].ps=i;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        if(i==1||a[i].v!=a[i-1].v){
            mx[cnt]=a[i-1].ps;
            mi[++cnt]=a[i].ps;
        }
    }
    mx[cnt]=a[n].ps;
    for(int i=1;i<=cnt;i++){
        if(flag==0){
            if(now>mx[i]) now=mi[i];
            else now=mx[i],flag=1;
        }
        else{
            if(now<mi[i]) now=mx[i];
            else flag=0,now=mi[i],ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}