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
	if (is_calculated_)
		return;
	is_calculated_ = true;
	
	child_->Calculate(expert_system_data);
	std::vector<Expression *> implies_which_contains_expression = expert_system_data.FindAllImpliesExpressions(this);
	for (Expression *implies_expression : implies_which_contains_expression) {
		implies_expression->Calculate(expert_system_data);
	}

	if (child_->GetState() == True && this->GetState() == True)
		throw std::runtime_error("logic contradiction");
		
	switch (unary_operator_) {
		case NOT:
			if (state_ < ApplyNot(child_->GetState())) {
				state_ = ApplyNot(child_->GetState());
			break;
		case PARENTHESES:
			if (state_ < child_->GetState()) {
				state_ = child_->GetState();
			}
			break;
		}
	}
}

void UnaryExpression::UpdateState(Expression::State state) {
	this->Expression::UpdateState(state);

	State child_new_state;
	switch (unary_operator_) {
		case NOT:
			if (state_ == True && child_->GetState() == True)
				throw std::runtime_error("logic contradiction");
			child_new_state = ApplyNot(state);
			break;
		case PARENTHESES:
			child_new_state = state;
			break;
	}

	child_->UpdateState(child_new_state);
}
