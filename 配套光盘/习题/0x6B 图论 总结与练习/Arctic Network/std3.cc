#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
typedef vector<int> VI;  typedef vector<vector<int> > VVI;
typedef vector<string> VS;  typedef vector<vector<string> > VVS;
typedef signed long long i64;  typedef unsigned long long u64;

double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

main() {
	int i, j, k, x, y, z, n;
	int N;
	int C, P;

	for( scanf( " %d", &N ); N; N--) {
		scanf( " %d %d", &C, &P );
		VI px(P), py(P);
		for( i = 0; i < P; i++ ) scanf( " %d %d", &px[i], &py[i] );
		if( C == P ) {printf( "0.00\n" ); continue;}
		vector<set<int> > sets(P);
		VI ps(P);
		for( i = 0; i < P; i++ ) sets[i].insert(i);
		for( i = 0; i < P; i++ ) ps[i] = i;
		vector<pair<double, pair<int, int> > > e;
		for( i = 0; i < P; i++ )
		for( j = i+1; j < P; j++ )
			e.push_back(pair<double, pair<int, int> >(
					dist(px[i], py[i], px[j], py[j]), pair<int, int>(i, j)));
		sort(e.begin(), e.end());
		int comp = P;
		for( i = 0; i < e.size(); i++ ) {
			x = e[i].second.first; y = e[i].second.second;
			set<int> &xs = sets[ps[x]], &ys = sets[ps[y]];
			if( !xs.count(y) ) {
				xs.insert(ys.begin(), ys.end());
				for( set<int>::iterator it = ys.begin(); it != ys.end(); it++ )
					ps[*it] = ps[x];
				if( --comp <= C ) break;
			}
		}
		printf( "%.2lf\n", e[i].first );
	}
}

