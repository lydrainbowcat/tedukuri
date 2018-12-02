// Author: ShakeCloud
// 递归法求值
#include <cstdio>
#include <cctype>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
stack<char> opt;stack<int> num;
string s;
int stat,i,cnt;

// inline bool isopt(char c)
// {
// 	return !('0'<=c&&c<='9')&&c!='('&&c!=')';
// }

int solve(int l,int r)
{
	if(l>r) return 0;
	stat=0;
	for(int i=r;i>=l;--i) 
	{
		if(s[i]=='(') --stat;if(s[i]==')') ++stat;
		if(!stat&&(s[i]=='+'||s[i]=='-'))
		{
			int v1=solve(l,i-1),v2=solve(i+1,r);
			if(s[i]=='-') v2*=-1;
			return v1+v2;
		};
	};
	stat=0;
	for(int i=r;i>=l;--i) 
	{
		if(s[i]=='(') --stat;if(s[i]==')') ++stat;
		if(!stat&&(s[i]=='*'||s[i]=='/'))
		{
			int v1=solve(l,i-1),v2=solve(i+1,r);
			if(s[i]=='*') v1*=v2; else v1/=v2;
			return v1;
		};
	};
	stat=0;
	for(int i=r;i>=l;--i) 
	{
		if(s[i]=='(') --stat;if(s[i]==')') ++stat;
		if(!stat&&s[i]=='^')
		{
			int v1=solve(l,i-1),v2=solve(i+1,r);
			int ret=1;while(v2--) ret*=v1;
			return ret;
		};
	};
	if(s[l]=='('&&s[r]==')') return solve(l+1,r-1);
	int ret=0;
	for(int i=l;i<=r;++i) {ret=ret*10+s[i]-'0';};
	return ret;
}
int main()
{
	cin >> s;
	for(i=0;i<=s.length()&&s[i]==')';++i);s.erase(s.begin(),s.begin()+i);
	for(i=s.length()-1;i>=0&&s[i]=='(';--i);s.erase(s.begin()+i+1,s.end());
	for(i=0;i<s.length();++i) 
		{if(s[i]=='(') ++stat;if(s[i]==')') --stat;};
	// printf("stat=%d\n",stat);
	if(stat>0) 
		for(i=0,cnt=0;cnt<stat&&i<s.length();++i) 
			if(s[i]=='(') {s.erase(s.begin()+i);--i;++cnt;};
	if(stat<0)
	{
		stat*=-1;
		for(i=0,cnt=0;cnt<stat&&i<s.length();++i) 
			if(s[s.length()-i-1]==')') {s.erase(s.length()-i-1);++cnt;--i;};
	};
	printf("%d\n",solve(0,s.length()-1));
	return 0;
}