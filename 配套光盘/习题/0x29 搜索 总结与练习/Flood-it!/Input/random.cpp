#include<iostream>
using namespace std; 
int n,t,i,j;
int main()
{
	freopen("floodit.in","w",stdout);
	cin>>n>>t;
	while(t--)
	{
		cout<<n<<endl;
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++) cout<<rand()%6<<' ';
			cout<<endl;
		}
	}
	cout<<0<<endl;
} 