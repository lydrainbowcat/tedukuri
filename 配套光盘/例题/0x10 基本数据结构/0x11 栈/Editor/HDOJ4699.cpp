#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000010;
const int INF=1e9;
int A[N],B[N],tpA,tpB;
int sum[N],f[N];
char ss[10];

int main()
{
    int Q;
    while(~scanf("%d",&Q)){
    sum[0]=0,f[0]=-INF; tpA=0,tpB=0;
    while(Q--)
    {
        scanf("%s",ss+1);
        if(ss[1]=='I')
        {
            int x;scanf("%d",&x);
            A[++tpA]=x;
            sum[tpA]=sum[tpA-1]+x;
            f[tpA]=max(f[tpA-1],sum[tpA]);
        }
        if(ss[1]=='D') tpA--;
        if(ss[1]=='L')
        {
            if(tpA)
            {
                int x=A[tpA]; tpA--;
                B[++tpB]=x;
            }
        }
        if(ss[1]=='R')
        {
            if(tpB)
            {
                int x=B[tpB]; tpB--;
                A[++tpA]=x;
                sum[tpA]=sum[tpA-1]+x;
                f[tpA]=max(f[tpA-1],sum[tpA]);
            }
        }
        if(ss[1]=='Q')
        {
            int k;scanf("%d",&k);
            printf("%d\n",f[k]);
        }
    }
    }
    return 0;
}