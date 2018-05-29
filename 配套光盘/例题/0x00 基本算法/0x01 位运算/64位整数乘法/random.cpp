#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
const long long m = 5e17;
int main() {
	srand((unsigned)time(0));
	putchar(rand()%9+'1');
	for(int i=0;i<17;i++) putchar(rand()%10+'0');
	puts("");
	putchar(rand()%9+'1');
	for(int i=0;i<17;i++) putchar(rand()%10+'0');
	puts("");
	putchar(rand()%9+'1');
	for(int i=0;i<17;i++) putchar(rand()%10+'0');
	puts("");
}

