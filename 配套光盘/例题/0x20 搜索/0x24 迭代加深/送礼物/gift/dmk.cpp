#include<cstdio>
#include<ctime>
#include<cstdlib>
int main()
{
    freopen("gift.in","w",stdout);
    srand(time(0));
    int m=2147483000;
    printf("%d 42\n",m);
    for (int i=1;i<=42;i++) printf("%d\n",(rand()*93)%22139001*97+1);
}
