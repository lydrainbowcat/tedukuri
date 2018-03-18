#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
deque<int> q[1010],p;
int c[1000010],n,m,i,j,x,t;
char s[10];

int main()
{
	while(cin>>n&&n)
	{
		p.clear();
		for(i=1;i<=n;i++) q[i].clear();
		for(i=1;i<=n;i++)
		{
			scanf("%d",&m);
			for(j=1;j<=m;j++) scanf("%d",&x),c[x]=i;
		}
		printf("Scenario #%d\n",++t);
		while(~scanf("%s",s)&&s[0]!='S')
			if(s[0]=='E')
			{
				scanf("%d",&x);
				if(!q[c[x]].size()) p.push_back(c[x]);
				q[c[x]].push_back(x);
			}
			else{
				x=p.front();
				printf("%d\n",q[x].front());
				q[x].pop_front();
				if(!q[x].size()) p.pop_front();
			}
		puts("");
	}
	return 0;
}