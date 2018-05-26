#include<iostream>
#include<set>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

int a[30005];
int b[30005];

int main()
{
	int m,n;
	while(~scanf("%d%d",&m,&n))
	{
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&b[i]);
		}
		priority_queue<int,vector<int>,greater<int> >q;
		priority_queue<int>q1;
		int i=0;
		int j=1;
		int k=1;
		int l=1;
		int x;
		while(j<=n)
		{
			if(i==b[j])
			{
				int res;
				j++;
				if(q1.size()<k)
				{
					res=q.top();
					q1.push(res);
					q.pop();

				}
				res=q1.top();
				printf("%d\n",res);
				k++;
			}
			else
			{
				i++;
				if(q1.size()<k)
				{
					q.push(a[i]);
					int x=q.top();
					q.pop();
					q1.push(x);
				}
				else if(q1.top()>a[i])
				{
					int x=q1.top();
					q1.pop();
					q1.push(a[i]);
					q.push(x);
				}
				else
				{
					q.push(a[i]);
				}
			}
		}
	}
	return 0;
}
