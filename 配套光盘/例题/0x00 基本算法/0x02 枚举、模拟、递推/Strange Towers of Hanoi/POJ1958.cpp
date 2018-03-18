/*
  Author: wccy
  本程序仅供参考 
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
int h3[20],h4[20];
void prev()
{
	h3[1]=1;
	for(int i=2;i<=12;i++) h3[i]=h3[i-1]*2+1;
	memset(h4,0x3f,sizeof h4);
	h4[1]=1;
	for(int i=2;i<=12;i++)
		for(int j=1;j<i;j++)
			h4[i]=min(h4[i],2*h4[j]+h3[i-j]);
}
void go()
{
	for(int i=1;i<=12;i++) printf("%d\n",h4[i]);
}
int main()
{
	prev();
	go();
	system("pause");
	return 0;
}
