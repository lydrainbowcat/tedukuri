#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime> 
using namespace std;
int n,i,j;
int main()
{
	freopen("input.txt","w",stdout);
	for(i=1;i<=100;i++)
	{
		n=rand()%100+1;
		if(i>15) n=100;
		cout<<n<<endl;
		for(j=1;j<=n;j++) printf("%d ",rand()%1000+1);
		cout<<endl;
	}
	return 0;
}
