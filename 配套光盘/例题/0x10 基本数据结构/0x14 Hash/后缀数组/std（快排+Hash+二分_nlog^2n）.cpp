#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int size = 300010;
unsigned long long f[size + 1], power[size + 1]; // hash
int sa[size + 1], rk[size + 1], height[size + 1], n;
char str[size];

unsigned long long get_hash(int l, int r) {
	return f[r] - f[l-1] * power[r-l+1];
}

// 最长公共前缀，二分+Hash 
int lcp(int x,int y) {
	int l=0, r=min(n-x+1,n-y+1);
	while(l<r) {
		int mid=(l+r+1)>>1;
		if(get_hash(x,x+mid-1)==get_hash(y,y+mid-1)) l=mid; else r=mid-1;
	}
	return l; 
}

// compare str[x~n] and str[y~n]
bool cmp(int x, int y) {
	int l = lcp(x, y); 
	return str[x+l]<str[y+l];
}

void calc_height() {
	for(int i=2;i<=n;i++) {
		height[i] = lcp(sa[i-1], sa[i]);
	}
}

int main()
{
	// 下标1~n，输出时再变回0~n-1 
	scanf("%s", str + 1);
	n = strlen(str + 1);
	power[0] = 1;
	for (int i = 1; i <= n; i++) {
		sa[i] = i;
		f[i] = f[i-1]*131 + (str[i]-'a'+1);
		power[i] = power[i-1] * 131; 
	} 
	sort(sa + 1, sa + n + 1, cmp);
	calc_height();
	for(int i = 1; i <= n; i++) printf("%d ", sa[i]-1); puts("");
	for(int i = 1; i <= n; i++) printf("%d ", height[i]); puts("");
	return 0;
}
