#pragma once

#include <vector>

#include "Expressions/Expression.hpp"
#include "Expressions/FactExpression.hpp"
#include "Expressions/UnaryExpression.hpp"
#include "Expressions/BinaryExpression.hpp"

class ExpertSystemData {
public:
	Expression *Find(Expression *expression) const;
	std::vector<Expression *> FindAllMainKeepers(Expression *expression) const;

	void AddMainExpression(Expression *expression);

	[[nodiscard]] const std::vector<Expression *> &GetMainExpressions() const;

	[[nodiscard]] const std::vector<Expression *> &GetFacts() const;

	[[nodiscard]] const std::vector<Expression *> &GetQuery() const;

private:
	std::vector<Expression *> main_expressions_;
	std::vector<Expression *> facts_;
	std::vector<Expression *> query_;
};