#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#define FILENAME "signal"
string ans1, ans2, ans3, out1, out2, out3;
int sc;
int main(int argc, char *argv[])
{
	ifstream out(FILENAME".out");
	ifstream std(argv[2]);
	ofstream score("score.log");
	ofstream report("report.log");
	
	std >> ans1 >> ans2 >> ans3;
	if (!(out >> out1 >> out2 >> out3)){
		report << "You didn't print enough numbers!" << endl;
		score << 0 << endl;
		report << "SJZEZ [Nescafe 26] Cup NOIP simulation contest. Special Judge powered by kAc." << endl;
		return 0;
	}
	report << "Part1(xor) : ";
	if (ans1 == out1){
		sc += 4;
		report << "Right!" << endl;
	}
	else{
		report << "Your answer " << out1 << " differs with stdandard answer " << ans1 << endl;
	}
	report << "Part2(and) : ";
	if (ans2 == out2){
		sc += 3;
		report << "Right!" << endl;
	}
	else{
		report << "Your answer " << out2 << " differs with stdandard answer " << ans2 << endl;
	}
	report << "Part3(or) : ";
	if (ans3 == out3){
		sc += 3;
		report << "Right!" << endl;
	}
	else{
		report << "Your answer " << out3 << " differs with stdandard answer " << ans3 << endl;
	}
	score << sc << endl;
	if (sc == 10)
		report << "Orz!!!!!!" << endl;
	report << "SJZEZ [Nescafe 26] Cup NOIP simulation contest. Special Judge powered by kAc." << endl;
	
}
