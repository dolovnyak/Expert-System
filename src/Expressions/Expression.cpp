#include "Expressions/Expression.hpp"
#include "ExpertSystem.hpp"
#include "ExpertSystemData.hpp"

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
			return "undetermined";
		case True:
			return "true";
	}
}

Expression::State Expression::GetMinState(Expression::State first, Expression::State second) {
	if (first < second)
		return first;
	return second;
}

Expression::State Expression::GetMaxState(Expression::State first, Expression::State second) {
	if (first > second)
		return first;
	return second;
}

void Expression::UpdateState(Expression::State state) {
	if (state > state_) {
		state_ = state;
	}
}

Expression::State Expression::GetState() const {
	return state_;
}

bool Expression::IsCalculated() const {
	return is_calculated_;
}

Expression::LogicContradictionException::LogicContradictionException(const std::string &exception)
: exception_("Logic contradiction was detected in '" + exception + "'") {}

const char* Expression::LogicContradictionException::what() const noexcept {
	return exception_.c_str();
}
