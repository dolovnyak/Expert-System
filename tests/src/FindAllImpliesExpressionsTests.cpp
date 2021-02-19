#include <ExpertSystem.hpp>
#include "gtest/gtest.h"

class FindAllImpliesExpressionsTests : public ::testing::Test {
public:
	friend ExpertSystemData;
	static void Assert_Eq(const std::vector<Expression *> &input_exprs, const ExpertSystemData::ExpressionsSet except_exprs) {
		ASSERT_EQ(input_exprs.size(), except_exprs.size());
		
		for (size_t i = 0; i < input_exprs.size(); i++) {
			ASSERT_TRUE(except_exprs.find(input_exprs[i]) != except_exprs.end());
		}
	}
};

TEST_F(FindAllImpliesExpressionsTests, FindAllImpliesExpressions_Implie) {
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
	FindAllImpliesExpressionsTests::Assert_Eq(data->FindAllImpliesExpressions(findExpression), exceptData->GetMainExpressions());
}

TEST_F(FindAllImpliesExpressionsTests, FindAllImpliesExpressions_Mutual_Implie) {
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
	FindAllImpliesExpressionsTests::Assert_Eq(data->FindAllImpliesExpressions(findExpression), exceptData->GetMainExpressions());
}
