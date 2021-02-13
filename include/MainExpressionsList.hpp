#pragma once

#include "Expressions.hpp"
#include "ExpressionSharedPtr.hpp"

class MainExpressionsList
{
public:
	static MainExpressionsList& Instance();
	
	std::shared_ptr<Expression> Find(const Expression& expression);
	
	void AddMainExpression(const Expression& expression);

//private:
	std::vector<Expression> main_expressions_list_;
};