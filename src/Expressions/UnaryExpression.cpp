#include "Expressions/UnaryExpression.hpp"

UnaryExpression::UnaryExpression(UnaryOperator unaryOperator, Expression* expression)
		: unary_operator_(unaryOperator), expression_(expression)
{
}

Expression* UnaryExpression::Find(Expression* expression)
{
	return nullptr;
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
