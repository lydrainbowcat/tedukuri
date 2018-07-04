/* Author: Adrian Kuegel
	Complexity: O(#solutions*length_solution*|alphabet| + n*m + n*n + m*m)
				= O(max(#solutions*length_solution*|alphabet|,(n+m)^2))
*/

#include <stdio.h>
#include <string.h>
#define max(x,y) ((x>y)?(x):(y))

int dp[81][81],nexta[80][26],nextb[80][26];

void construct(int i, int j, int len, char out[81]) {
	int k;
	if (len == dp[0][0]) {
		out[len] = 0;
		printf("%s\n",out);
		return;
	}
	for (k=0; k<26; k++) {
		int a=nexta[i][k],b=nextb[j][k];
		if (a>=0 && b>=0 && (!len && dp[a-1][b-1] == dp[0][0] || dp[a-1][b-1] == dp[i-1][j-1]-1)) {
			out[len] = k+'a';
			construct(a,b,len+1,out);
		}
	}
}

int main() {
	int i,j,n,m;
	char s1[81],s2[81],out[81];
	gets(s1);
	gets(s2);
	n = strlen(s1);
	m = strlen(s2);
	/*	standard DP algorithm to find the length of
	longest common subsequence(s) */
	for (i=0; i<=n; i++)
		dp[i][m] = 0;
	for (j=0; j<=m; j++)
		dp[n][j] = 0;
	for (i=n-1; i>=0; --i)
		for (j=m-1; j>=0; --j)
			if (s1[i] == s2[j])
				dp[i][j] = dp[i+1][j+1]+1;
			else
				dp[i][j] = max(dp[i][j+1],dp[i+1][j]);
	/* calculate the next occurance of a letter j after position i in first string */
	for (i=0; i<n; i++) {
		for (j=0; j<26; j++)
			nexta[i][j] = -1;
		for (j=i; j<n; j++)
			if (nexta[i][s1[j]-'a']<0)
				nexta[i][s1[j]-'a'] = j+1;
	}
	/* calculate the next occurance of a letter j after position i in second string */
	for (i=0; i<m; i++) {
		for (j=0; j<26; j++)
			nextb[i][j] = -1;
		for (j=i; j<m; j++)
			if (nextb[i][s2[j]-'a']<0)
				nextb[i][s2[j]-'a'] = j+1;
	}
	construct(0,0,0,out);
	return 0;
}
