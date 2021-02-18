#include "Expressions/BinaryExpression.hpp"
#include "ExpertSystemData.hpp"

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

void BinaryExpression::Calculate(ExpertSystemData &expert_system_data) {
	if (is_calculated_)
		return;
	is_calculated_ = true;
	
	std::vector<Expression *> implies_which_contains_expression = expert_system_data.FindAllImpliesExpressions(this);
	for (Expression *implies_expression : implies_which_contains_expression) {
		implies_expression->Calculate(expert_system_data);
	}
	left_child_->Calculate(expert_system_data);
	right_child_->Calculate(expert_system_data);

	// TODO implement
	switch (binary_operator_) {
		case AND:
			state_ = Expression::GetMinState(left_child_->GetState(), right_child_->GetState()) > state_ ?
					Expression::GetMinState(left_child_->GetState(), right_child_->GetState()) : state_;
			break;
		case OR:
			state_ = Expression::GetMaxState(left_child_->GetState(), right_child_->GetState()) > state_ ?
					 Expression::GetMaxState(left_child_->GetState(), right_child_->GetState()) : state_;
			break;
		case XOR:
			//TODO ?????????
			break;
		case IMPLIES:
			right_child_->UpdateState(left_child_->GetState());
			break;
		case MUTUAL_IMPLIES:
			right_child_->UpdateState(left_child_->GetState());
			left_child_->UpdateState(right_child_->GetState());
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
			if (left_child_->GetState() < state && right_child_->GetState() < state) {
				left_child_->UpdateState(Undetermined);
				right_child_->UpdateState(Undetermined);
			}
			break;
		case XOR:
//			bool equals = left_child_->GetState() != Undetermined && left_child_->GetState() == right_child_->GetState();
//			if (state == Undetermined) {
//
//				if (!equals) {
//					left_child_->UpdateState(True);
//					right_child_->UpdateState(True);
//				}
//			} else if (state == True) {
//				if (equals) {
//
//				}
//			}
			break;
		case IMPLIES:
		case MUTUAL_IMPLIES:
			throw std::logic_error("Must be not reachable");
	}
}

BinaryOperator BinaryExpression::GetBinaryOperator() const {
	return binary_operator_;
}


