#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;
int n;
int main() {
    srand((unsigned)time(0));
    cin>>n;
    cout<<n<<endl;
    for(int i=1;i<=n;i++) printf("%d ", rand()&(1u<<31)-1);
    cout<<endl;
}