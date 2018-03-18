#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[10010],b[10010],c[210],fa[10010],n,m,i,j,x,y,t,ans;

int get(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}

int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(i=1;i<=m;i++) scanf("%d%d",&a[i],&b[i]);
		for(i=1;i<=n;i++) {scanf("%d",&x); c[x]=i;}
		if(m>3*n-6) {cout<<"NO\n"; continue;}
		for(i=1;i<=2*m;i++) fa[i]=i;
		for(i=1;i<m;i++)
			for(j=i+1;j<=m;j++)
				if((long long)(c[a[j]]-c[a[i]])*(c[a[j]]-c[b[i]])*(c[b[j]]-c[a[i]])*(c[b[j]]-c[b[i]])<0)
				{
					x=get(i); y=get(j+m);
					if(x!=y) fa[y]=x;
					x=get(i+m); y=get(j);
					if(x!=y) fa[y]=x;
				}
		for(ans=i=1;i<=m;i++)
			if(get(i)==get(i+m)) ans=0;
		if(ans) cout<<"YES\n"; else cout<<"NO\n";
	}
	return 0;
}