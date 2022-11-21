#include "pch.h"
#include "C:\Users\User\source\repos\oop_prakt2\oop_prakt2\gamestate.cpp"
#include "C:\Users\User\source\repos\oop_prakt2\oop_prakt2\arbitrator.cpp"
#include "C:\Users\User\source\repos\oop_prakt2\oop_prakt2\strategies.cpp"
#include "C:\Users\User\source\repos\oop_prakt2\oop_prakt2\strenumconv.cpp"
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

TEST(GameStart, CreatingPlayer) {
	GameState dilemma;
	vector<strategies> strats = { strategies::allcooperate, strategies::alldefect, strategies::notstated };
	ASSERT_DEATH({ dilemma.start(strats, 1, 'd'); }, "Error while creating the player\n");
}

TEST(PlayerLogic, Alldefect) {
	alldefect alld;
	char ch;
	for (int i = 0; i < 100; i++) {
		ch = alld.make_step();
		ASSERT_EQ(ch, 'D');
	}
}
TEST(PlayerLogic, Allcooperate) {
	allcooperate allc;
	char ch;
	for (int i = 0; i < 100; i++) {
		ch = allc.make_step();
		ASSERT_EQ(ch, 'C');
	}
}
TEST(PlayerLogic, Grim) {
	grim gr;
	char ch;
	for (int i = 0; i < 50; i++) {
		ch = gr.make_step();
		gr.enter_choice(std::vector<char>{'C', 'C'});
		ASSERT_EQ(ch, 'C');
	}
	gr.enter_choice(std::vector<char>{'D', 'C'});
	for (int i = 0; i < 50; i++) {
		ch = gr.make_step();
		gr.enter_choice(std::vector<char>{'C', 'C'});
		ASSERT_EQ(ch, 'D');
	}
}

TEST(PlayerLogic, TitForTat) {
	titfortat ttt;
	char ch;

	ch = ttt.make_step();
	ASSERT_EQ(ch, 'C');

	ttt.enter_choice(std::vector<char>{'C', 'C'});
	ch = ttt.make_step();
	ASSERT_EQ(ch, 'C');

	ttt.enter_choice(std::vector<char>{'D', 'C'});
	ch = ttt.make_step();
	ASSERT_EQ(ch, 'D');

	ttt.enter_choice(std::vector<char>{'C', 'C'});
	ch = ttt.make_step();
	ASSERT_EQ(ch, 'C');
}

TEST(PlayerLogic, DetectiveTTT) {
	detective d;
	char ch;

	ch = d.make_step();
	ASSERT_EQ(ch, 'C');
	d.enter_choice(std::vector<char>{'C', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');
	d.enter_choice(std::vector<char>{'C', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'C');
	d.enter_choice(std::vector<char>{'D', 'D'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');

	d.enter_choice(std::vector<char>{'C', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'C');
	d.enter_choice(std::vector<char>{'C', 'D'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');
	d.enter_choice(std::vector<char>{'D', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');
	d.enter_choice(std::vector<char>{'D', 'D'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');
	d.enter_choice(std::vector<char>{'C', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'C');
}

TEST(PlayerLogic, DetectiveD) {
	detective d;
	char ch;

	ch = d.make_step();
	ASSERT_EQ(ch, 'C');
	d.enter_choice(std::vector<char>{'C', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');
	d.enter_choice(std::vector<char>{'C', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'C');
	d.enter_choice(std::vector<char>{'C', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');

	d.enter_choice(std::vector<char>{'C', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');
	d.enter_choice(std::vector<char>{'C', 'D'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');
	d.enter_choice(std::vector<char>{'D', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');
	d.enter_choice(std::vector<char>{'D', 'D'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');
	d.enter_choice(std::vector<char>{'C', 'C'});
	ch = d.make_step();
	ASSERT_EQ(ch, 'D');

}


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
