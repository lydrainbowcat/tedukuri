#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
long long dp[13][1<<13];
bool check(int s){
	int rest=0;
	while(s){
		if(s&1)rest+=1;
		else if(rest&1)return 0;
		s>>=1;
	}
	if(rest&1)return 0;
	return 1;
}
int main(){
	int n,m;
	while(~scanf("%d%d",&n,&m)){
		if(n==0||m==0)return 0;
		memset(dp,0,sizeof(dp));
		int tot=(1<<m);
		for(int i=0;i<tot;i++){
			if(check(i))dp[1][i]=1;
		}
		for(int i=1;i<n;i++){
			for(int j=0;j<tot;j++){
				if(!dp[i][j])continue;
				for(int k=0;k<tot;k++){
					if((k|j)!=tot-1||(!check(k&j)))continue;
					dp[i+1][k]+=dp[i][j];
				}
			}
		}
		printf("%lld\n",dp[n][tot-1]);
	}
}
