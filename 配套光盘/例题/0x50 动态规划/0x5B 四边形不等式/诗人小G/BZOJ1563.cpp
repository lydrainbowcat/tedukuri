#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long double f[100010];
long long sum[100010];
int a[100010],b[100010],c[100010],len[100010],n,L,P,i,j,l,r,mid,h,p,t;
char s[50];

int get(int i)
{
	l=1; r=p;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(a[mid]<=i&&b[mid]>=i) return c[mid];
		if(i<a[mid]) r=mid-1; else l=mid+1;
	}
}

long double calc(int i,int j)
{
	long long x=sum[i]-sum[j]+i-j-1-L;
	long double temp=1;
	x=x>0?x:-x;
	for(int k=1;k<=P;k++) temp*=x;
	return temp+f[j];
}

void pop(int i)
{
	while(h<=p)
		if(b[h]<=i) h++;
		else {a[h]=i+1; break;}
}

void push(int i)
{
	int k=-1;
	while(h<=p)
	{
		if(calc(a[p],i)<=calc(a[p],c[p])) {k=a[p]; p--;}
		else{
			if(calc(b[p],c[p])<=calc(b[p],i)) break;
			l=a[p]; r=b[p];
			while(l<r)
			{
				mid=(l+r)>>1;
				if(calc(mid,i)<=calc(mid,c[p])) r=mid; else l=mid+1;
			}
			b[p]=l-1; k=l;
			break;
		}
	}
	if(k==-1) return;
	a[++p]=k; b[p]=n; c[p]=i;
}

int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>L>>P;
		for(i=1;i<=n;i++)
		{
			scanf("%s",s);
			len[i]=strlen(s);
			sum[i]=sum[i-1]+len[i];
		}
		f[0]=0; h=p=1;
		a[1]=1; b[1]=n; c[1]=0;
		for(i=1;i<=n;i++)
		{
			j=get(i);
			f[i]=calc(i,j);
			pop(i);
			push(i);
		}
		if(f[n]>1e18) cout<<"Too hard to arrange\n";
		else cout<<(long long)f[n]<<endl;
		for(i=1;i<=20;i++) putchar('-');
		cout<<endl;
	}
	return 0;
}