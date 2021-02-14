#include "Expressions/UnaryExpression.hpp"

UnaryExpression::UnaryExpression(UnaryOperator unaryOperator, Expression* expression)
		: unary_operator_(unaryOperator), expression_(expression)
{
}

Expression* UnaryExpression::Find(Expression* expression)
{
	if (*this == *expression)
		return this;
	
	return expression_->Find(expression);
}

std::string UnaryExpression::ToString() const
{
	return UnaryOperatorToString(unary_operator_) + expression_->ToString();
}

std::string UnaryExpression::UnaryOperatorToString(UnaryOperator unaryOperator) const
{
	switch (unaryOperator)
	{
		case UnaryOperator::NOT: return "!";
	}
}

ExpressionType UnaryExpression::GetType() const
{
	return ExpressionType::UNARY;
}

bool UnaryExpression::operator==(const Expression& expression) const
{
	if (expression.GetType() != ExpressionType::UNARY)
		return false;
	
	const UnaryExpression* unaryExpression = dynamic_cast<const UnaryExpression* >(&expression);
	if (unary_operator_ != unaryExpression->unary_operator_ ||
		*expression_ != *unaryExpression->expression_)
		return false;
	
	return true;
}

bool UnaryExpression::operator!=(const Expression& expression) const
{
	return !(*this == expression);
}
