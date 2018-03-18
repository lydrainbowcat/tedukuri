/*
    Author: wccy
    本程序仅供参考
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

#define maxn 1005

int n;
int f[maxn];

void input()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &f[i]);
    if (n & 1)
        f[n++] = 0;
}

void work()
{
    int ans = 0;
    for (int i = n - 1; i > 0; i -= 2)
        ans ^= f[i] - f[i - 1] - 1;
    if (ans)
        printf("Georgia will win\n");
    else
        printf("Bob will win\n");
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        input();
        sort(f, f + n);
        work();
    }
    return 0;
}