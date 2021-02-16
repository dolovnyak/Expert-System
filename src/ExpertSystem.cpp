#include "ExpertSystem.hpp"
#include "MainExpressionsList.hpp"
#include "Visualizer.hpp"

int yyparse();
extern FILE *yyin;

void ExpertSystem::Setup(FILE* file)
{
	MainExpressionsList::Instance().main_expressions_list_.clear();

	yyin = file;
	yyparse();
	std::cout << "expressions num: " << MainExpressionsList::Instance().main_expressions_list_.size() << std::endl;
	fclose(file);
}

/// Works with data from ExpertSystem class
void ExpertSystem::Solve() {
	for (const auto request : query_) {
		request->Calculate(*this);
	}
}

std::vector<Expression *> ExpertSystem::FindAllOwners(Expression *expression) {
	// TODO check
	std::vector<Expression *> result(main_expressions_.size());
	for (auto main_expression : main_expressions_) {
		if (main_expression->Find(expression) != nullptr) {
			result.push_back(expression);
		}
	}
	return result;
}
