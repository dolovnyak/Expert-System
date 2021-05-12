#include "ExpertSystem.hpp"
#include "gtest/gtest.h"

bool contains(const std::string& orig, const std::string& income)
{
	std::size_t found = orig.find(income);
	
	if (found != std::string::npos)
		return true;
	return false;
}

class Not_Correct_Input_Tests : public ::testing::Test {
public:
	static std::string GetSimpleInput() {
		return "A => !A\n"
		 		"?A\n";
	}
	
	static std::string GetNotSimpleInput() {
		return "A => B\n"
		 		"B => !A\n"
	 			"?A\n";
	}
};

TEST_F(Not_Correct_Input_Tests, Not_Correct_Input_Tests_Simple_Nothing_True) {
    try {
        char *str = strdup(GetSimpleInput().c_str());
        ExpertSystemData *data = ExpertSystem::Parse(str);
        ExpertSystem::Solve(*data);
        ASSERT_TRUE(false);
    }
    catch (const std::exception& e) {
        ASSERT_TRUE(contains(e.what(), "Logic contradiction was detected"));
    }
}

TEST_F(Not_Correct_Input_Tests, Not_Correct_Input_Tests_Simple_A_True) {
	char *str = strdup((GetSimpleInput() + "=A").c_str());
	try {
		ExpertSystemData *data = ExpertSystem::Parse(str);
		ExpertSystem::Solve(*data);
		ASSERT_TRUE(false);
	}
	catch (const std::exception &exception) {
		ASSERT_TRUE(contains(exception.what(), "Logic contradiction"));
	}
}

TEST_F(Not_Correct_Input_Tests, Not_Correct_Input_Tests_Not_Simple_A_True) {
	char *str = strdup((GetNotSimpleInput() + "=A").c_str());
	try {
		ExpertSystemData *data = ExpertSystem::Parse(str);
		ExpertSystem::Solve(*data);
		ASSERT_TRUE(false);
	}
	catch (const std::exception &exception) {
		ASSERT_TRUE(contains(exception.what(), "Logic contradiction"));
	}
}

TEST_F(Not_Correct_Input_Tests, Not_Correct_Input_Tests_Not_Simple_B_True) {
	char *str = strdup((GetNotSimpleInput() + "=B").c_str());
	ExpertSystemData *data = ExpertSystem::Parse(str);
	ExpertSystem::Solve(*data);
	FactExpression query_expr = FactExpression('A');
	ASSERT_TRUE((*data->GetQueries().find(&query_expr))->GetState() == Expression::State::False);
}

TEST_F(Not_Correct_Input_Tests, Not_Correct_Input_Tests_Not_Simple_AB_True) {
	char *str = strdup((GetNotSimpleInput() + "=AB").c_str());
	try {
		ExpertSystemData *data = ExpertSystem::Parse(str);
		ExpertSystem::Solve(*data);
		ASSERT_TRUE(false);
	}
	catch (const std::exception &exception) {
		ASSERT_TRUE(contains(exception.what(), "Logic contradiction"));
	}
}
