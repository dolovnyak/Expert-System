#include "Expressions/BinaryExpression.hpp"

BinaryExpression::BinaryExpression(Expression* left, BinaryOperator binaryOperator, Expression* right)
		: left_child_(left), binary_operator_(binaryOperator), right_child_(right)
{
}

Expression* BinaryExpression::Find(Expression* expression)
{
	if (*this == *expression)
		return this;

	Expression *temp = left_child_->Find(expression);
	if (temp != nullptr)
		return temp;
	return right_child_->Find(expression);
}

std::string BinaryExpression::GetString(BinaryOperator binaryOperator)
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
	return left_child_->ToString() + GetString(binary_operator_) + right_child_->ToString();
}

ExpressionType BinaryExpression::GetType() const
{
	return ExpressionType::BINARY;
}

bool BinaryExpression::operator==(const Expression& expression) const
{
	if (expression.GetType() != ExpressionType::BINARY)
		return false;
	
	const auto* binaryExpression = dynamic_cast<const BinaryExpression* >(&expression);
	if (binary_operator_ != binaryExpression->binary_operator_ ||
		*left_child_ != *binaryExpression->left_child_ ||
		*right_child_ != *binaryExpression->right_child_)
		return false;
	
	return true;
}

bool BinaryExpression::operator!=(const Expression& expression) const
{
	return !(*this == expression);
}

void BinaryExpression::Calculate(ExpertSystem &expert_system) {
	this->Expression::Calculate(expert_system);

	left_child_->Calculate(expert_system);
	right_child_->Calculate(expert_system);

	// TODO implement
	switch (binary_operator_) {
		case AND:
			break;
		case OR:
			break;
		case XOR:
			break;
		case IMPLIES:
			break;
		case MUTUAL_IMPLIES:
			break;
	}
}

void BinaryExpression::UpdateState(Expression::State state) {
	this->Expression::UpdateState(state);

	// TODO implement
	switch (binary_operator_) {
		case AND:
			left_child_->UpdateState(state);
			right_child_->UpdateState(state);
			break;
		case OR:
			break;
		case XOR:
			break;
		case IMPLIES:
			break;
		case MUTUAL_IMPLIES:
			break;
	}
}


