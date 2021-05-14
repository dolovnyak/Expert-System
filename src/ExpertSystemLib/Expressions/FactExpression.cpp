#include "Expressions/FactExpression.hpp"
#include "ExpertSystemData.hpp"

FactExpression::FactExpression(char fact)
		: fact_(fact) {}

Expression *FactExpression::Find(Expression *expression) {
	if (*this == *expression)
		return this;

	return nullptr;
}

std::string FactExpression::ToString() const {
	return std::string(1, fact_);
}

ExpressionType FactExpression::GetType() const {
	return ExpressionType::FACT;
}

bool FactExpression::operator==(const Expression &expression) const {
	if (expression.GetType() != ExpressionType::FACT)
		return false;

	const auto *factExpression = dynamic_cast<const FactExpression *>(&expression);
	if (fact_ != factExpression->fact_)
		return false;

	return true;
}

bool FactExpression::operator!=(const Expression &expression) const {
	return !(*this == expression);
}

char FactExpression::GetFact() const {
	return fact_;
}

void FactExpression::Calculate(ExpertSystemData &expert_system_data)
{
	std::vector<Expression *> implies_which_contains_expression = expert_system_data.FindAllImpliesExpressions(this);
	for (Expression *implies_expression : implies_which_contains_expression) {
		implies_expression->Calculate(expert_system_data);
	}
}
