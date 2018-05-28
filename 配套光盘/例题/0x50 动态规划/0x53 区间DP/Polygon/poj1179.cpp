#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
const int M = 60;
int n,a[2*M],f[2*M][2*M],f1[2*M][2*M];
char b[2*M];
int main()
{
	memset(f,-0x3f,sizeof f);
	memset(f1,0x3f,sizeof f1);
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
	getchar(),scanf("%c%d",&b[i],&a[i]),b[i+n] = b[i],a[i+n] = a[i];
	for(int i = 1; i <= 2*n;i ++) f1[i][i] = f[i][i] = a[i]; 
		for(int j = 2; j <= n;j++)
			for(int k = 1; j + k - 1 <= 2 * n; k++)
				for(int l = k+1;l <= j + k - 1; l++)
				{
					
					if(b[l] == 't')
					{
						f[k][j+k-1] = max(f[k][j+k-1],f[k][l-1] + f[l][j+k-1]);
						f1[k][j+k-1] = min(f1[k][j+k-1],f1[k][l-1] + f1[l][j+k-1]);
					}
					else
					{
						f[k][j+k-1] = max(f[k][j+k-1],f[k][l-1] * f[l][j+k-1]);
						f[k][j+k-1] = max(f[k][j+k-1],f1[k][l-1] * f1[l][j+k-1]);
						f1[k][j+k-1] = min(f1[k][j+k-1],f1[k][l-1] * f1[l][j+k-1]);
						f1[k][j+k-1] = min(f1[k][j+k-1],f1[k][l-1] * f[l][j+k-1]);
						f1[k][j+k-1] = min(f1[k][j+k-1],f[k][l-1] * f1[l][j+k-1]);
						f1[k][j+k-1] = min(f1[k][j+k-1],f[k][l-1] * f[l][j+k-1]);
					}
				}
	int maxx = -0x7fffffff;	
	for(int i = 1; i <= n; i++)
	maxx = max(maxx,f[i][i+n-1]);	
	printf("%d\n", maxx);
	for(int i = 1; i <= n; i++)
		if(f[i][i+n-1] == maxx)
		printf("%d ",i);
	return 0;
}