#include "pch.h"
#include "C:\Users\User\source\repos\oop_prakt2\oop_prakt2\gamestate.cpp"
#include "C:\Users\User\source\repos\oop_prakt2\oop_prakt2\arbitrator.cpp"
#include "C:\Users\User\source\repos\oop_prakt2\oop_prakt2\strategies.cpp"
#include <iostream>
#include <map>
#include <string>
using namespace std;
class dilemmal : public ::testing::Test {
protected:
	void SetUp(int nsteps, char mode) {
		GameState d();
	}
};

TEST(Construct, ReadFile) {
	GameState dilemma("C:/Users/User/source/repos/oop_prakt2/test/okmatrix.csv");
	map<string, string> okmatrix = { {"CCC", "123"}, {"CCD", "123"}, {"CDC", "123"}, {"DCC", "123"},
					{"CDD", "123"}, {"DCD", "123"}, {"DDC", "123"}, {"DDD", "123"} };
	ASSERT_EQ(okmatrix, dilemma.get_rules());
	ASSERT_DEATH({ GameState d("C:/Users/User/source/repos/oop_prakt2/test/mistake1matrix.csv"); }, "Input file values are wrong\n");
	ASSERT_DEATH({ GameState d("C:/whereisnosuchfile.csv"); }, "Matrix file haven't read\n");
}

char** string_to_char(string str) {
	string temp;
	char** inparams = new char*;
	int pos = 1;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != ' ') {
			temp.push_back(str[i]);
		}
		else {
			inparams[pos] = new char[temp.size()];
			for (int j = 0; j < temp.size(); j++) {
				inparams[pos][j] = temp[j];
			}
			temp.resize(0);
			pos++;
		}
	}
	return inparams;
}

TEST(Parser, Test) {
	int argc = 4;
	string input = "--mode=detailed --steps=10 --matrix=C:/Users/User/source/repos/oop_prakt2/test/okmatrix.csv";
	char** argv = string_to_char(input);
	for (int i = 0; i < argc; i++) {
		cout << string(argv[i]) << endl;
	}
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
