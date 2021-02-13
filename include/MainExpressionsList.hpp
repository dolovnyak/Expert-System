#pragma once

#include "Expressions.hpp"
#include "ExpressionSharedPtr.hpp"

class MainExpressionsList
{
public:
	static MainExpressionsList& Instance();
	
	std::shared_ptr<Expression> Find(ExpressionSharedPtr expression);
	
	void AddMainExpression(const ExpressionSharedPtr& expression);

private:
	std::vector<ExpressionSharedPtr> main_expressions_list_;
};