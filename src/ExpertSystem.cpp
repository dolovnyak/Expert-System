#include "ExpertSystem.hpp"
#include "MainExpressionsList.hpp"
#include "Visualizer.hpp"

int yyparse();
extern FILE *yyin;

void ExpertSystem::Execute(FILE* file)
{
	MainExpressionsList::Instance().main_expressions_list_.clear();
	yyin = file;
	yyparse();
	std::cout << "expressions num: " << MainExpressionsList::Instance().main_expressions_list_.size() << std::endl;
	fclose(file);
}
