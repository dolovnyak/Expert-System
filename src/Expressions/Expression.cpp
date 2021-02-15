#include "Expressions/Expression.hpp"

std::ostream& operator<<(std::ostream& os, const Expression& expression)
{
	os << expression.ToString();
	return os;
}
