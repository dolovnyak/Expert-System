#include <ExpertSystem.hpp>
#include "gtest/gtest.h"

class FindAllImpliesExpressionsTests : public ::testing::Test {
public:
	static void Assert_Eq(const std::vector<Expression *> &inputExprs, const std::vector<Expression *> &exceptExprs) {
		ASSERT_EQ(inputExprs.size(), exceptExprs.size());
		
		for (int i = 0; i < inputExprs.size(); i++) {
			ASSERT_EQ(*inputExprs[i], *exceptExprs[i]);
		}
	}
};

TEST_F(FindAllImpliesExpressionsTests, FindAllImpliesExpressions_Implie) {
	ExpertSystemData data = ExpertSystem::Parse(
			"A => C\n"
			"A | B => M | D\n"
			"K => A\n"
			"D => O + (A | M)\n"
			"J => O + (!((A)) | M)\n");
	ExpertSystemData exceptData = ExpertSystem::Parse(
			"K => A\n"
			"D => O + (A | M)\n"
			"J => O + (!((A)) | M)\n");
	Expression *findExpression = new FactExpression('A');
	FindAllImpliesExpressionsTests::Assert_Eq(data.FindAllImpliesExpressions(findExpression), exceptData.GetMainExpressions());
}

TEST_F(FindAllImpliesExpressionsTests, FindAllImpliesExpressions_Mutual_Implie) {
	ExpertSystemData data = ExpertSystem::Parse(
			"A <=> C\n"
			"A | B <=> M | D\n"
			"K + A <=> D\n"
			"D => O + (A | M)\n"
			"D => O + (M)\n"
			"J => O + (!((A)) | M)\n");
	ExpertSystemData exceptData = ExpertSystem::Parse(
			"A <=> C\n"
			"A | B <=> M | D\n"
			"K + A <=> D\n"
			"D => O + (A | M)\n"
			"J => O + (!((A)) | M)\n");
	Expression *findExpression = new FactExpression('A');
	FindAllImpliesExpressionsTests::Assert_Eq(data.FindAllImpliesExpressions(findExpression), exceptData.GetMainExpressions());
}
