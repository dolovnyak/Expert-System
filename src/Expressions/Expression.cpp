#include "Expressions/Expression.hpp"

std::ostream& operator<<(std::ostream& os, const Expression& expression)
{
	os << expression.ToString();
	return os;
}

std::string Expression::GetStateName(Expression::State state) {
	switch (state) {
		case False:
			return "false";
		case Undetermined:
			return "???";
		case True:
			return "true";
	}
}

void Expression::Calculate(ExpertSystem &expert_system) {
	for (const auto owner : expert_system.FindAllOwners(this)) {
		owner->Calculate(expert_system);
	}
}

void Expression::UpdateState(Expression::State state) {
	if (state > state_) {
		state_ = state;
		// TODO logging
	} else if (state < state_) {
		// TODO error or something else
	}
}

Expression::State Expression::GetState() const {
	return state_;
}
