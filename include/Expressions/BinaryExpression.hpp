#pragma once

#include <ExpertSystem.hpp>

#include "Expression.hpp"

enum BinaryOperator {
	AND = 0,
	OR,
	XOR,
	IMPLIES,
	MUTUAL_IMPLIES
};

class BinaryExpression : public Expression {
public:
	BinaryExpression(Expression *left, BinaryOperator binary_operator, Expression *right);

	Expression *Find(Expression *expression) override;

	[[nodiscard]] std::string ToString() const override;

	[[nodiscard]] ExpressionType GetType() const override;
	
	bool operator==(const Expression &expression) const override;

	bool operator!=(const Expression &expression) const override;

	[[nodiscard]] Expression *GetLeftChild() const { return left_child_; }
	
	[[nodiscard]] BinaryOperator GetBinaryOperator() const;

	[[nodiscard]] Expression *GetRightChild() const { return right_child_; }

	void Calculate(ExpertSystemData &expert_system_data) override;
	
	void UpdateBinaryOperator(BinaryOperator binary_operator);

protected:
	void UpdateState(State state) override;

private:
	Expression *left_child_;
	BinaryOperator binary_operator_;
	Expression *right_child_;
	
	[[nodiscard]] static std::string GetString(BinaryOperator binary_operator) ;
};
