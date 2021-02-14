#pragma once

#include "Expressions/Expression.hpp"

class FactExpression : public Expression
{
public:
	FactExpression(char fact);
	
	Expression* Find(Expression* expression) override;
	
	std::string ToString() const override;

private:
	char fact_;
};
