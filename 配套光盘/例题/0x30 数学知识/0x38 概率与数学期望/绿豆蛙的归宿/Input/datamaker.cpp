#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int d[100005];
vector<pair<int,int> > e;
int main()
{
	freopen("input10", "w", stdout);
	srand(time(0));
	int N=100000;
	for(int i=2;i<N;i++){
		int fa=rand()%(i-1)+1;
		e.push_back(make_pair(i, fa));
		d[fa]++;
	}
	for(int i=1;i<N;i++)
		if(d[i]==0){
			e.push_back(make_pair(N,i));
		}
	printf("%d %lu\n",N,e.size());
	for (vector<pair<int, int>>::iterator it=e.begin(); it!=e.end(); it++) {
		printf("%d %d %d\n",it->second,it->first,rand()%10000);
	}
    return 0;
}

