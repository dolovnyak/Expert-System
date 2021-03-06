#include "gtest/gtest.h"

#include "ExpertSystem.hpp"

class Not_Tests : public ::testing::Test {
public:
	const std::string Test1_Input = "B + !C => A\n"
									"?A\n";

	const std::string Test_Empty = "=\n";
	const std::string Test_B = "=B\n";
	const std::string Test_C = "=C\n";
	const std::string Test_BC = "=BC\n";

public:
	static ExpertSystemData *Solve(const std::string &input, const std::string &init_facts) {
		auto *esd = ExpertSystem::Parse(const_cast<char *>((input + init_facts).c_str()));
		ExpertSystem::Solve(*esd);
		return esd;
	}

	static void Check(const ExpertSystemData *esd,
					  const std::vector<char> &facts,
					  Expression::State state) {
		for (char c : facts) {
			auto f = std::find_if(esd->GetFacts().begin(), esd->GetFacts().end(), [c](const Expression *e) {
				return dynamic_cast<const FactExpression *>(e)->GetFact() == c;
			});
			ASSERT_EQ((*f)->GetState(), state);
		}
	}
};

TEST_F(Not_Tests, Test_Empty) {
	auto *esd = Solve(Test1_Input, Test_Empty);
	Check(esd, {'A'}, Expression::False);
	delete esd;
}

TEST_F(Not_Tests, Test_B) {
	auto *esd = Solve(Test1_Input, Test_B);
	Check(esd, {'A'}, Expression::True);
	delete esd;
}

TEST_F(Not_Tests, Test_C) {
	auto *esd = Solve(Test1_Input, Test_C);
	Check(esd, {'A'}, Expression::False);
	delete esd;
}

TEST_F(Not_Tests, Test_BC) {
	auto *esd = Solve(Test1_Input, Test_BC);
	Check(esd, {'A'}, Expression::False);
	delete esd;
}
