#include "ExpertSystem.hpp"
#include "gtest/gtest.h"

class Correct_XOR_Operations_Tests : public ::testing::Test {
public:
	static std::string GetSimpleInput() {
	return "B + C => A\n"
			"D ^ E => B\n"
			"B => C\n"
			"?A\n";
	}
	
	static std::string GetNonStandardInput() {
		return "M => A ^ C\n"
			   "A ^ C => L\n"
			   "?ACL\n";
	}
};

TEST_F(Correct_XOR_Operations_Tests, Correct_XOR_Operations_Tests_Nothing_True) {
	char *str = strdup(GetSimpleInput().c_str());
	ExpertSystemData *data = ExpertSystem::Parse(str);
	ExpertSystem::Solve(*data);
	FactExpression query_expr = FactExpression('A');
	ASSERT_TRUE((*data->GetQueries().find(&query_expr))->GetState() == Expression::State::False);
}

TEST_F(Correct_XOR_Operations_Tests, Correct_XOR_Operations_Tests_D_True) {
	char *str = strdup((GetSimpleInput() + "=D").c_str());
	ExpertSystemData *data = ExpertSystem::Parse(str);
	ExpertSystem::Solve(*data);
	FactExpression query_expr = FactExpression('A');
	ASSERT_TRUE((*data->GetQueries().find(&query_expr))->GetState() == Expression::State::True);
}

TEST_F(Correct_XOR_Operations_Tests, Correct_XOR_Operations_Tests_E_True) {
	char *str = strdup((GetSimpleInput() + "=E").c_str());
	ExpertSystemData *data = ExpertSystem::Parse(str);
	ExpertSystem::Solve(*data);
	FactExpression query_expr = FactExpression('A');
	ASSERT_TRUE((*data->GetQueries().find(&query_expr))->GetState() == Expression::State::True);
}

TEST_F(Correct_XOR_Operations_Tests, Correct_XOR_Operations_Tests_DE_True) {
	char *str = strdup((GetSimpleInput() + "=DE").c_str());
	ExpertSystemData *data = ExpertSystem::Parse(str);
	ExpertSystem::Solve(*data);
	FactExpression query_expr = FactExpression('A');
	ASSERT_TRUE((*data->GetQueries().find(&query_expr))->GetState() == Expression::State::False);
}

TEST_F(Correct_XOR_Operations_Tests, Correct_Xor_Operation_Non_Standart_Nothing_True) {
	char *str = strdup(GetNonStandardInput().c_str());
	ExpertSystemData *data = ExpertSystem::Parse(str);
	ExpertSystem::Solve(*data);
	FactExpression query_expr_A = FactExpression('A');
	FactExpression query_expr_C = FactExpression('C');
	FactExpression query_expr_L = FactExpression('L');
	ASSERT_TRUE((*data->GetQueries().find(&query_expr_A))->GetState() == Expression::State::False);
	ASSERT_TRUE((*data->GetQueries().find(&query_expr_C))->GetState() == Expression::State::False);
	ASSERT_TRUE((*data->GetQueries().find(&query_expr_L))->GetState() == Expression::State::False);
}

TEST_F(Correct_XOR_Operations_Tests, Correct_Xor_Operation_Non_Standart_M_True) {
	char *str = strdup((GetNonStandardInput() + "=M").c_str());
	ExpertSystemData *data = ExpertSystem::Parse(str);
	ExpertSystem::Solve(*data);
	FactExpression query_expr_A = FactExpression('A');
	FactExpression query_expr_C = FactExpression('C');
	FactExpression query_expr_L = FactExpression('L');
	ASSERT_TRUE((*data->GetQueries().find(&query_expr_A))->GetState() == Expression::State::Undetermined);
	ASSERT_TRUE((*data->GetQueries().find(&query_expr_C))->GetState() == Expression::State::Undetermined);
	ASSERT_TRUE((*data->GetQueries().find(&query_expr_L))->GetState() == Expression::State::True);
}
