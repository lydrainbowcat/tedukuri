// Author: LiRe
#include <iostream>
#include <cstdio>
using namespace std;
bool map[2500][2500];
int edge[10];

void dfs(int n, int x, int y) {
	if(n == 1) {
		map[x][y] = 1;
		return;
	}
	int e = edge[n - 1];
	dfs(n - 1, x, y);
	dfs(n - 1, x + 2 * e, y);
	dfs(n - 1, x + e, y + e);
	dfs(n - 1, x, y + 2 * e);
	dfs(n - 1, x + 2 * e, y + 2 * e);	
}


void print(int n) {
	dfs(n, 1, 1);
	for(int i = 1; i <= edge[n]; ++i) {
		for(int j = 1; j <= edge[n]; ++j) {
			if(map[i][j] == 0) cout<<' ';
			else cout<<'X';
		}
		cout<<endl;
	}
	cout<<"-"<<endl;
}

int main() {
	edge[1] = 1;
	for(int i = 2; i <= 7; ++i) edge[i] = edge[i - 1] * 3;
	int n;
	while(cin>>n) {
		if(n == -1) break;
		print(n); 
	}	
	return 0;
}