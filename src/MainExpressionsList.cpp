#include "MainExpressionsList.hpp"

MainExpressionsList& MainExpressionsList::Instance()
{
	static MainExpressionsList mainExpressionsList;
	return mainExpressionsList;
}

Expression* MainExpressionsList::Find(Expression* expression)
{
	// parse all main_expressions_list_ in depth
	for (Expression* expression : main_expressions_list_)
	{
	
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
