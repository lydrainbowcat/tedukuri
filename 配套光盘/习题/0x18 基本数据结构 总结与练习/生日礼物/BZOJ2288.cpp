#include<iostream>
#include<cstdio>
using namespace std;
int a[100010],b[100010],L[100010],R[100010],q[100010],v[100010];
int n,m,t,p,ans,i,temp,x;

void up(int p)
{
	while(p>1)
		if(b[q[p]]<b[q[p>>1]])
		{
			swap(q[p],q[p>>1]);
			swap(v[q[p]],v[q[p>>1]]);
			p>>=1;
		}
		else break;
}

void down(int l,int r)
{
	int t=2*l;
	while(t<=r)
	{
		if(t<r&&b[q[t]]>b[q[t+1]]) t++;
		if(b[q[l]]>b[q[t]])
		{
			swap(q[l],q[t]);
			swap(v[q[l]],v[q[t]]);
			l=t,t=2*l;
		}
		else break;
	}
}

void insert(int i)
{
	q[++p]=i; v[i]=p;
	up(p);
}
void erase(int i)
{
	v[q[p]]=v[i];
	q[v[i]]=q[p]; p--;
	up(v[i]);
	down(v[i],p);
}

int main()
{
	cin>>n>>t;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(;n&&a[n]<=0;n--);
	for(i=1;i<=n&&a[i]<=0;i++);
	if(i>n) {puts("0"); return 0;}
	for(;i<=n;i++)
		if(a[i]>0&&a[i-1]>0 || a[i]<=0&&a[i-1]<=0) b[m]+=a[i];
		else b[++m]=a[i];
	for(i=1;i<=m;i++)
		if(b[i]>0) temp++,ans+=b[i]; else b[i]=-b[i];
	if(temp<=t) {cout<<ans<<endl; return 0;}
	for(i=1;i<=m;i++)
	{
		L[i]=i-1,R[i-1]=i;
		insert(i);
	}
	for(i=t;i<temp;i++)
	{
		ans-=b[x=q[1]];
		if(!L[x])
		{
			erase(x),erase(R[x]);
			L[R[R[x]]]=0;
		}
		else if(!R[x])
		{
			erase(x),erase(L[x]);
			R[L[L[x]]]=0;
		}
		else{
			erase(L[x]),erase(R[x]),erase(x);
			b[x]=b[L[x]]+b[R[x]]-b[x];
			insert(x);
			L[x]=L[L[x]],R[L[x]]=x;
			R[x]=R[R[x]],L[R[x]]=x;
		}
	}
	cout<<ans<<endl;
	return 0;
}