#include"testlib.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	registerValidation();
	int n=inf.readInt(2,100000,"n");
	inf.readSpace();
	int m=inf.readInt(1,100000,"m");
	inf.readSpace();
	int p=inf.readInt(1,100,"p");
	inf.readEoln();
	for(int i=1;i<n;i++)
	{
		if(i>1) inf.readSpace();
		inf.readInt(1,9999,"Di");
	}
	inf.readEoln();
	int x,y;
	while(m--)
	{
		x=inf.readInt(1,n,"Hi");
		inf.readSpace();
		y=inf.readInt(0,1000000000,"Ti");
		inf.readEoln();
	}
  inf.readEof();
}
