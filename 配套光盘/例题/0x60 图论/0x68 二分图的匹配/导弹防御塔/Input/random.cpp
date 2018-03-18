#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime> 
using namespace std;
int n,m,t1,t2,V,i; 
int main()
{
	freopen("missle.in","w",stdout);
	srand((unsigned)time(0)); 
	cin>>n>>m;
	t1=rand()%2000+1;
	t2=rand()%2000+1;
	V=rand()%2000+1; 
	cout<<n<<' '<<m<<' '<<t1<<' '<<t2<<' '<<V<<endl;
	for(i=1;i<=n+m;i++) printf("%d %d\n",rand()%10000,rand()%10000); 
	return 0;
}
