// Author: SJZEZ wccy
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
int T;
inline string get(string a)
{
	vector<string> str;
	string res="";
	int cnt=0,tot=0,st=0;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]=='0') tot++;
		else tot--;
		if(!tot)
		{
			str.push_back("0"+get(a.substr(st+1,i-1-st))+"1");
			st=i+1;
		}
	}
	sort(str.begin(),str.end());
	for(int i=0;i<str.size();i++) res+=str[i];
	return res;
}
int main()
{
	scanf("%d",&T);
	string s1,s2;
	while(T--)
	{
		cin >> s1 >> s2;
		if(get(s1)==get(s2)) printf("same\n");
		else printf("different\n");
	}
	return 0;
}