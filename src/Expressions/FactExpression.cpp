#include "Expressions/FactExpression.hpp"

FactExpression::FactExpression(char fact)
		: fact_(fact)
{
}

Expression* FactExpression::Find(Expression* expression)
{
	return nullptr;
}

std::string FactExpression::ToString() const
{
	return std::string(1, fact_);
}
