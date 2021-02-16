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
	switch (unary_operator_) {
		case NOT:
			return "!" + expression_->ToString();
		case PARENTHESES:
			return "(" + expression_->ToString() + ")";
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
