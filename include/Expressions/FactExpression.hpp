#pragma once

#include "Expressions/Expression.hpp"

class FactExpression : public Expression {
public:
	explicit FactExpression(char fact);

	Expression *Find(Expression *expression) override;

	[[nodiscard]] std::string ToString() const override;

	[[nodiscard]] ExpressionType GetType() const override;

	bool operator==(const Expression &expression) const override;

	bool operator!=(const Expression &expression) const override;

	char GetFact() const;

private:
	char fact_;
};
