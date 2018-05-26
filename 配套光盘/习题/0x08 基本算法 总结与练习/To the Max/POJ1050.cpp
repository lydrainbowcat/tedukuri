#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=1e4+10;
int i,j,k,n;
int mp[M][M];
int d[M];
int main()
{
    while(~scanf("%d",&n))
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            scanf("%d",&mp[i][j]);
        int ans=0;
        for(i=0;i<n;i++){
        memset(d,0,sizeof(d));
        for(j=i;j<n;j++){
            for(k=0;k<n;k++){
                d[k]+=mp[j][k];
            }
            int sum=0;
            for(k=0;k<n;k++){
                sum+=d[k];
                ans=max(ans,sum);
                if(sum<0)sum=0;
            }
          }
       }
       printf("%d\n",ans);
    }
    return  0;
}