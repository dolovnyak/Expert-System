#include "MainExpressionsList.hpp"

MainExpressionsList& MainExpressionsList::Instance()
{
	static MainExpressionsList mainExpressionsList;
	return mainExpressionsList;
}

Expression* MainExpressionsList::Find(Expression* expression)
{
	for (Expression* curExpression : main_expressions_list_)
	{
		if (curExpression->Find(expression) != nullptr)
			return curExpression->Find(expression);
	}
	return nullptr;
}

void MainExpressionsList::AddMainExpression(Expression* expression)
{
	if (Find(expression) != nullptr) //if two identical rules
		return;
	else
		main_expressions_list_.push_back(expression);
}
