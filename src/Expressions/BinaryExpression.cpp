#include "Expressions/BinaryExpression.hpp"

BinaryExpression::BinaryExpression(Expression* left, BinaryOperator binaryOperator, Expression* right)
		: left_expression_(left), binary_operator_(binaryOperator), right_expression_(right)
{
}

Expression* BinaryExpression::Find(Expression* expression)
{
	if (*this == *expression)
		return this;
	
	if (left_expression_->Find(expression) != nullptr)
		return left_expression_->Find(expression);
	return right_expression_->Find(expression);
}

std::string BinaryExpression::BinaryOperatorToString(BinaryOperator binaryOperator) const
{
	switch (binaryOperator)
	{
		case BinaryOperator::AND: return "+";
		case BinaryOperator::OR: return "|";
		case BinaryOperator::XOR: return "^";
		case BinaryOperator::IMPLIES: return "=>";
		case BinaryOperator::MUTUAL_IMPLIES: return "<=>";
	}
}

std::string BinaryExpression::ToString() const
{
	return left_expression_->ToString() + BinaryOperatorToString(binary_operator_) + right_expression_->ToString();
}

ExpressionType BinaryExpression::GetType() const
{
	return ExpressionType::BINARY;
}

bool BinaryExpression::operator==(const Expression& expression) const
{
	if (expression.GetType() != ExpressionType::BINARY)
		return false;
	
	const BinaryExpression* binaryExpression = dynamic_cast<const BinaryExpression* >(&expression);
	if (binary_operator_ != binaryExpression->binary_operator_ ||
		*left_expression_ != *binaryExpression->left_expression_ ||
		*right_expression_ != *binaryExpression->right_expression_)
		return false;
	
	return true;
}

bool BinaryExpression::operator!=(const Expression& expression) const
{
	return !(*this == expression);
}


