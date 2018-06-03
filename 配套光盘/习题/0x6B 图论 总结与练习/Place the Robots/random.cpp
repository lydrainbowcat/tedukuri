#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
using namespace std;
int main() {
	srand((unsigned)time(0));
	cout<<11<<endl;
	for(int T=1;T<=11;T++) {
		int n=50,m=50;
		cout<<n<<' '<<m<<endl;
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) {
				char ch;
				int k=rand()%6;
				if(k<3) ch='o';
				else if(k<5) ch='*';
				else ch='#';
				putchar(ch);
			}
			puts("");
		}
	}
}
