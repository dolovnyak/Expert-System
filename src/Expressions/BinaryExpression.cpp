#include "Expressions/BinaryExpression.hpp"

BinaryExpression::BinaryExpression(Expression* left, BinaryOperator binaryOperator, Expression* right)
		: left_expression_(left), binary_operator_(binaryOperator), right_expression_(right)
{
}

Expression* BinaryExpression::Find(Expression* expression)
{
	return nullptr;
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

