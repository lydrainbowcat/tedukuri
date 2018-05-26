#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 20000

int n,m,ans;
pair<int,int> cow[MAXN],lotion[MAXN];

priority_queue<int> q;

void process(){
        int i,i1;
        while(!q.empty()) q.pop();
        sort(cow,cow+n);
        sort(lotion,lotion+m);
        for(ans=i=i1=0;i<m;i++){
                while((i1<n)&&(cow[i1].first<=lotion[i].first))
                        q.push(-cow[i1++].second);
                while((!q.empty())&&(-(q.top())<lotion[i].first))
                        q.pop();
                while((!q.empty())&&(lotion[i].second--)){
                        ans++;
                        q.pop();
                }
        }
}


int main(){
        int i,j;
	freopen("tanning.in","r",stdin);
	freopen("tanning.out","w",stdout);
        scanf("%d%d",&n,&m);
        for(i=0;i<n;i++)
                scanf("%d%d",&cow[i].first,&cow[i].second);
        for(i=0;i<m;i++)
                scanf("%d%d",&lotion[i].first,&lotion[i].second);
        ans=0;
        process();
        printf("%d\n",ans);
        return 0;
}