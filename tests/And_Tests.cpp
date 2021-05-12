#include "gtest/gtest.h"

#include "ExpertSystem.hpp"

class And_Tests : public ::testing::Test {
public:
	const std::string Test1_Input = "B => A\n"
								   "D + E => B\n"
								   "G + H => F\n"
								   "I + J => G\n"
								   "G => H\n"
								   "L + M => K\n"
								   "O + P => L + N\n"
								   "N => M\n"
								   "?AFKP\n";

	const std::string Test_DEIJOP = "=DEIJOP\n";
	const std::string Test_DEIJP = "=DEIJP\n";

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

TEST_F(And_Tests, Test_DEIJOP) {
	auto *esd = Solve(Test1_Input, Test_DEIJOP);
	Check(esd, {'A', 'F', 'K', 'P'}, Expression::True);
	delete esd;
}

TEST_F(And_Tests, Test_DEIJP) {
	auto *esd = Solve(Test1_Input, Test_DEIJP);
	Check(esd, {'A', 'F', 'P'}, Expression::True);
	Check(esd, {'K'}, Expression::False);
	delete esd;
}
