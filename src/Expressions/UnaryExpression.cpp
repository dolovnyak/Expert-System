#include "Expressions/UnaryExpression.hpp"
#include "ExpertSystem.hpp"
#include "ExpertSystemData.hpp"

UnaryExpression::UnaryExpression(UnaryOperator unaryOperator, Expression* child)
		: unary_operator_(unaryOperator), child_(child) {}

Expression* UnaryExpression::Find(Expression* expression)
{
	if (*this == *expression)
		return this;
	
	return child_->Find(expression);
}

std::string UnaryExpression::ToString() const
{
	switch (unary_operator_) {
		case NOT:
			return "!" + child_->ToString();
		case PARENTHESES:
			return "(" + child_->ToString() + ")";
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
	
	const auto* unaryExpression = dynamic_cast<const UnaryExpression* >(&expression);
	if (unary_operator_ != unaryExpression->unary_operator_ ||
		*child_ != *unaryExpression->child_)
		return false;
	
	return true;
}

bool UnaryExpression::operator!=(const Expression& expression) const
{
	return !(*this == expression);
}

static inline Expression::State ApplyNot(Expression::State state) {
	switch (state) {
		case Expression::State::False:
			return Expression::State::True;
		case Expression::State::Undetermined:
			return Expression::State::Undetermined;
		case Expression::State::True:
			return Expression::State::False;
	}
}

void UnaryExpression::Calculate(ExpertSystemData &expert_system_data) {
	child_->Calculate(expert_system_data);
	switch (unary_operator_) {
		case NOT:
			if (state_ < ApplyNot(child_->GetState())) {
				Expression::UpdateState(child_->GetState());
			} else if (child_->GetState() < ApplyNot(state_)) {
				child_->UpdateState(state_);
			}
			break;
		case PARENTHESES:
			if (state_ < child_->GetState()) {
				Expression::UpdateState(child_->GetState());
			} else if (child_->GetState() < state_) {
				child_->UpdateState(state_);
			}
			break;
	}
}

void UnaryExpression::UpdateState(Expression::State state) {
	this->Expression::UpdateState(state);

	State child_new_state;
	switch (unary_operator_) {
		case NOT:
			child_new_state = ApplyNot(state);
			break;
		case PARENTHESES:
			child_new_state = state;
			break;
	}

	child_->UpdateState(child_new_state);
}
