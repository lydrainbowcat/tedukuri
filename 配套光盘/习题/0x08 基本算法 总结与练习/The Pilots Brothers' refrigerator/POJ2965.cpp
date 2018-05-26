// Author: LiRe
#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

int res[5][5];

int main() {
	char m;
	for(int i = 1; i <= 4; ++i) {
		for(int j = 1; j <= 4; ++j) {
			cin>>m;
			if(m == '+') {
				for(int k = 1; k <= 4; ++k)
					res[i][k] ^= 1,
					res[k][j] ^= 1;
				res[i][j] ^= 1;
			}
		}
	}
	int cnt = 0;
	for(int i = 1; i <= 4; ++i) 
		for(int j = 1; j <= 4; ++j) 
			if(res[i][j]) 
				++cnt;
	cout<<cnt<<endl;
	for(int i = 1; i <= 4; ++i) 
		for(int j = 1; j <= 4; ++j)
			if(res[i][j])
				cout<<i<<" "<<j<<endl;
	return 0;	
}