#pragma once

#include <vector>
#include "Expressions/Expression.hpp"
#include "Expressions/BinaryExpression.hpp"
#include "Expressions/UnaryExpression.hpp"
#include "Expressions/FactExpression.hpp"

class MainExpressionsList
{
public:
	static MainExpressionsList& Instance();
	
	Expression* Find(Expression* expression);
	
	void AddMainExpression(Expression* expression);

//private:
	std::vector<Expression*> main_expressions_list_;
};