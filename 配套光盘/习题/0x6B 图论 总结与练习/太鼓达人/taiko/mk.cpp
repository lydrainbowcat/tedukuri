#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<time.h>
using namespace std;
#define fr(i,n) for(int i=0;i<n;i++)
#define fo(i,n) for(int i=1;i<=n;i++)
#define fe(i,n) for(__typeof(n.begin()) i=n.begin();i!=n.end();i++)
int n,m,x,y;
string s="taiko0";
void wk(string s,int n)
{
	freopen((s+".in").c_str(),"w",stdout);
	cerr << ("taiko.exe <"+s+".in"+" >"+s+".out").c_str() << endl;
	printf("%d\n",n);
	fclose(stdout);
	system(("taiko.exe <"+s+".in"+" >"+s+".out").c_str());
}
int main()
{
	srand(time(0));
	for(char i='0';i<='9';i++)
		s[5]=i,wk(s,i-'0'+2);
}
