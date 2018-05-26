#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
multiset<int> a;
multiset<int>::iterator it;
int n,i,b,c,x;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		if(scanf("%d",&x)==EOF) x=0;
		a.insert(x);
		if(i==1) c+=x;
		else{
			b=1<<30;
			it=a.find(x);
			if(it!=a.begin()) it--,b=x-(*it),it++;
			it++; if(it!=a.end()) b=min(b,(*it)-x);
			c+=b;
		}
	}
	cout<<c<<endl;
	return 0;
}