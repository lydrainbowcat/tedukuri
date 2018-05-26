// Author: LiRe
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define db double
#define point pair<db, db>
#define l first
#define r second

int N;
db R;
point p[1003];
db pos[1003];
int cnt;

bool cmp(point x, point y) {
	return x.r == y.r ? x.l < y.l : x.r < y.r;
}

inline void getx(db ta, db tb, db& le, db &ri) {
	db m = sqrt(R * R - tb * tb);
	le = ta - m; ri = ta + m;
}

inline bool check(db ta, db tb) {
	if(tb > R) return false;
	else if(tb < 0) return false;
	return true;
}

int main() {
	int T = 0;
	db ta, tb;
	while(cin>>N>>R) {
		if(!N || !R) break;
		++T;
		bool flag = 0;
		for(int i = 1; i <= N; ++i) {
			cin>>ta>>tb;
			if(!check(ta, tb)) flag = 1;
			getx(ta, tb, p[i].l, p[i].r);
		}
		if(flag) {
			cout<<"Case "<<T<<": "<<-1<<endl;
			continue;
		} 
		sort(p + 1, p + N + 1, cmp);
		cnt = 1; 
		db tmp = p[1].r;
		for(int i = 2; i <= N; ++i) {
			if(p[i].l > tmp) {
				cnt++;
				tmp = p[i].r;
			} else {
				tmp = min(p[i].r, tmp);
			}
		}
		cout<<"Case "<<T<<": "<<cnt<<endl;
	}
}