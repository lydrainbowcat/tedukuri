#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

int n,a0,a1,b0,b1,ans;

int gcd(int a,int b)
{
    return b == 0 ? a : gcd(b,a % b);
}

long long lcm(int a,int b)
{
    return (long long)a * b / gcd(a,b);
}


void solve(int x)
{
    if (gcd(x,a0) == a1 && lcm(x,b0) == b1)
    ans++;
}

int main()
{
   scanf("%d",&n);
   while (n--)
   {
       ans = 0;
       scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
       for (int i = 1; i <= sqrt(b1); i++)
       if (b1 % i == 0)
       {
           solve(i);
           if (i * i != b1)
           solve(b1 / i);
       }
       printf("%d\n",ans);
   }    

 }