#include "Expressions/FactExpression.hpp"

FactExpression::FactExpression(char fact)
		: fact_(fact)
{
}

Expression* FactExpression::Find(Expression* expression)
{
	if (*this == *expression)
		return this;
	
	return nullptr;
}

std::string FactExpression::ToString() const
{
	return std::string(1, fact_);
}

ExpressionType FactExpression::GetType() const
{
	return ExpressionType::FACT;
}

bool FactExpression::operator==(const Expression& expression) const
{
	if (expression.GetType() != ExpressionType::FACT)
		return false;
	
	const FactExpression* factExpression = dynamic_cast<const FactExpression* >(&expression);
	if (fact_ != factExpression->fact_)
		return false;
	
	return true;
}

bool FactExpression::operator!=(const Expression& expression) const
{
	return !(*this == expression);
}
