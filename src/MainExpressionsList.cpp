#include "MainExpressionsList.hpp"

MainExpressionsList& MainExpressionsList::Instance()
{
	static MainExpressionsList mainExpressionsList;
	return mainExpressionsList;
}

std::shared_ptr<Expression> MainExpressionsList::Find(const Expression& expression)
{
	// parse all main_expressions_list_ in depth
	return nullptr;
}

void MainExpressionsList::AddMainExpression(const Expression& expression)
{
	std::cout << "it work" << std::endl;
	if (Find(expression) != nullptr) //if two identical rules
		return;
	else
		main_expressions_list_.push_back(expression);
}
