#pragma once

#include "Expressions/Expression.hpp"

enum UnaryOperator {
	NOT = 0,
	PARENTHESES
};

class UnaryExpression : public Expression {
public:
	UnaryExpression(UnaryOperator unary_operator, Expression *expression);
	
	bool operator==(const Expression &expression) const override;
	
	bool operator!=(const Expression &expression) const override;

	Expression *Find(Expression *expression) override;
	
	void Calculate(ExpertSystemData &expert_system_data) override;

	[[nodiscard]] std::string ToString() const override;

	[[nodiscard]] ExpressionType GetType() const override;

	[[nodiscard]] Expression *GetChild() const { return child_; }
	
	[[nodiscard]] UnaryOperator GetUnaryOperator() const { return unary_operator_; }

protected:
	void UpdateState(State state) override;

private:
	UnaryOperator unary_operator_;
	Expression *child_;
};
