#include"testlib.h"
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<map>
using namespace std;
int main(int argc,char* argv[])
{
	registerGen(argc,argv);
	int n=rnd.next(10,100),m=rnd.next(50,200),p=rnd.next(10,100);
	cout<<n<<' '<<m<<' '<<p<<endl;
	for(int i=1;i<n;i++)
	{
		if(i>1) putchar(' ');
		printf("%d",rnd.next(1,99));
	}
	cout<<endl;
	for(int i=1;i<=m;i++)
	{
		int x=rnd.next(1,n),y=rnd.next(0,n*100);
		printf("%d %d\n",x,y);
	}
}
