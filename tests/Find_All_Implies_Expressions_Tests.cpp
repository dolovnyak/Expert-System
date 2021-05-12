#include <ExpertSystem.hpp>
#include "gtest/gtest.h"

class Find_All_Implies_Expressions_Tests : public ::testing::Test {
public:
	friend ExpertSystemData;
	static void Assert_Eq(const std::vector<Expression *> &input_exprs, const ExpertSystemData::ExpressionsSet& except_exprs) {
		ASSERT_EQ(input_exprs.size(), except_exprs.size());
		
		for (auto input_expr : input_exprs) {
			ASSERT_TRUE(except_exprs.find(input_expr) != except_exprs.end());
		}
	}
};

TEST_F(Find_All_Implies_Expressions_Tests, FindAllImpliesExpressions_Implie) {
	char input[1024] = "A => C\n"
						"A | B => M | D\n"
						"K => A\n"
						"D => O + (A | M)\n"
	  					"J => O + (!((A)) | M)\n";
	ExpertSystemData *data = ExpertSystem::Parse(input);
	char except_input[1024] = "K => A\n"
							"D => O + (A | M)\n"
		 					"J => O + (!((A)) | M)\n";
	ExpertSystemData *exceptData = ExpertSystem::Parse(except_input);
	Expression *findExpression = new FactExpression('A');
	Find_All_Implies_Expressions_Tests::Assert_Eq(data->FindAllImpliesExpressions(findExpression), exceptData->GetMainExpressions());
}

TEST_F(Find_All_Implies_Expressions_Tests, FindAllImpliesExpressions_Mutual_Implie) {
	char input[1024] = "A <=> C\n"
					"A | B <=> M | D\n"
	 				"K + A <=> D\n"
					"D => O + (A | M)\n"
					"D => O + (M)\n"
					"J => O + (!((A)) | M)\n";
	ExpertSystemData *data = ExpertSystem::Parse(input);
	char except_input[1024] = "A <=> C\n"
							  "A | B <=> M | D\n"
							  "K + A <=> D\n"
							  "D => O + (A | M)\n"
		 					  "J => O + (!((A)) | M)\n";
	ExpertSystemData *exceptData = ExpertSystem::Parse(except_input);
	Expression *findExpression = new FactExpression('A');
	Find_All_Implies_Expressions_Tests::Assert_Eq(data->FindAllImpliesExpressions(findExpression), exceptData->GetMainExpressions());
}
