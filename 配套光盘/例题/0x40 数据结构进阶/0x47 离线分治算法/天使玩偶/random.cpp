#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int N = 500000;
const int M = 500000;

int posrand()
{
	int sign = rand()&1;
	if(!sign) sign = -1;
	return rand()*sign;
}

int main(void)
{
	freopen("kdt.in","wt",stdout);
	srand(time(NULL));
	printf("%d %d\n",N,M);
	for(int i = 0;i < N;i++) printf("%d %d\n",posrand(),posrand());
	for(int i = 0;i < M;i++) printf("%d %d %d\n",rand()%2+1,posrand(),posrand());
	return 0;
}
