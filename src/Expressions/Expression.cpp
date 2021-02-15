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
