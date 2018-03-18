#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<map>
using namespace std;
int n,m,t,i,x,y;
map<pair<int,int>,int> hash;
int main()
{
	freopen("tanabata.in","w",stdout);
	srand((unsigned)time(0));
	cin>>n>>m>>t;
	cout<<n<<' '<<m<<' '<<t<<endl; 
	for(i=1;i<=t;i++)
	{
		do{x=rand()%n+1; y=rand()%m+1;}while(hash[make_pair(x,y)]);
		hash[make_pair(x,y)]=1;
		printf("%d %d\n",x,y);
	}
	return 0;
}
