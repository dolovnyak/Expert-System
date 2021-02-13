#include "MainExpressionsList.hpp"

MainExpressionsList& MainExpressionsList::Instance()
{
	static MainExpressionsList mainExpressionsList;
	return mainExpressionsList;
}

void MainExpressionsList::AddMainExpression(const ExpressionSharedPtr& expression)
{
	if (Find(expression) != nullptr) //if two identical rules
		return;
	else
		main_expressions_list_.push_back(expression);
}

std::shared_ptr<Expression> MainExpressionsList::Find(ExpressionSharedPtr expression)
{
	// parse all main_expressions_list_ in depth
	return nullptr;
}
