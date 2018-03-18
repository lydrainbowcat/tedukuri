#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
priority_queue<int> q;
int n,a[100010],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		q.push(-a[i]);
	}
	for(int i=1;i<n;i++)
	{
		int x=-q.top(); q.pop();
		int y=-q.top(); q.pop();
		ans+=x+y;
		q.push(-x-y);
	}
	cout<<ans<<endl;
}