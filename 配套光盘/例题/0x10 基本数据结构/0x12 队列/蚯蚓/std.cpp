// Author: A_Comme_Amour
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define p u/v
long long n,m,len,t,a,u,v;
const int MAXN=1e7+1;
int que[MAXN],que1[MAXN],que2[MAXN];
int tail1,tail2,tail3,head1,head2,head3;

inline int read()
{
    int now=0; char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9')
    {
        now=(now<<1)+(now<<3)+ch-'0';
        ch=getchar();
    } 
    return now;
}

void write(int x)
{
    if (x<0) {putchar('-');x=-x;}
    if (x>9) write(x/10);
    putchar(x%10+'0');
}

int find(int x)//查询第x秒最长的蚯蚓 
{
    int a,b,c,d; a=b=c=d=-1;
    if (head1<=tail1) b=que[head1]+x*len;
    if (head2<=tail2) c=que1[head2]+x*len;
    if (head3<=tail3) d=que2[head3]+x*len;
    a=max(b,max(c,d));//找出最长的蚯蚓  
    if (a==b) head1++;//判断是在哪个队列中，并将其弹出 
    else//三者之中选一个
    {
        if (a==c) head2++;
        else head3++;
    }
    return a;
}

bool comp(int a,int b)
{
    return a>b;
}

int main()
{
    n=read(); m=read(); len=read(); u=read(); v=read(); t=read();
    for (int i=1; i<=n; i++)
        que[i]=read();
    sort(que+1,que+1+n,comp);
    tail1=n; head1=head2=head3=1;
    for (int i=1; i<=m; i++)
    {
        int x=find(i-1);
        if (i%t==0) {write(x); putchar(' ');}
        int new1=x*p;
        int new2=x-new1;
        que1[++tail2]=new1-i*len;
        que2[++tail3]=new2-i*len;
    }
    putchar('\n');
    for (int i=1; i<=n+m; i++)
    {
        int x=find(m);
        if (i%t==0) {write(x); putchar(' ');}
    }
    return 0;
}
