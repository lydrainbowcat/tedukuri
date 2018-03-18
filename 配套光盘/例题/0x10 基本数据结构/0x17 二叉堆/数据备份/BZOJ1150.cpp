#include<iostream>
#include<cstdio>
using namespace std;
int f[100010],a[100010],pre[100010],next[100010],v[100010];
int n,m,p,i,x,ans;

void up(int p)
{
	while(p>1)
		if(a[f[p]]<a[f[p>>1]])
		{
			swap(f[p],f[p>>1]);
			swap(v[f[p]],v[f[p>>1]]);
			p>>=1;
		}
		else break;
}

void down(int l,int r)
{
	int t=2*l;
	while(t<=r)
	{
		if(t<r&&a[f[t]]>a[f[t+1]]) t++;
		if(a[f[l]]>a[f[t]])
		{
			swap(f[l],f[t]);
			swap(v[f[l]],v[f[t]]);
			l=t,t=2*l;
		}
		else break;
	}
}

void insert(int x)
{
	f[++p]=x; v[x]=p;
	up(p);
}

void erase(int x)
{
	f[v[x]]=f[p]; v[f[p]]=v[x]; p--;
	up(v[x]),down(v[x],p);
}

int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<n;i++)
	{
		a[i]=a[i+1]-a[i];
		next[i]=i+1,pre[i+1]=i;
		insert(i);
	}
	for(i=1;i<=m;i++)
	{
		x=f[1]; ans+=a[x];
		if(pre[x]==0&&next[x]==n) break;
		if(pre[x]==0)
		{
			erase(x),erase(next[x]);
			pre[next[next[x]]]=0;
		}
		else if(next[x]==n)
		{
			erase(x),erase(pre[x]);
			next[pre[pre[x]]]=n;
		}
		else{
			erase(x),erase(pre[x]),erase(next[x]);
			a[x]=a[pre[x]]+a[next[x]]-a[x];
			insert(x);
			pre[x]=pre[pre[x]]; next[pre[x]]=x;
			next[x]=next[next[x]]; pre[next[x]]=x;
		}
	}
	cout<<ans<<endl;
	return 0; 
}