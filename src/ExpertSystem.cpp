#include "ExpertSystem.hpp"
#include "MainExpressionsList.hpp"
#include "Visualizer.hpp"

extern void ShowExampleAppCustomNodeGraph(bool* opened);
int yyparse();
extern FILE *yyin;

void ExpertSystem::Execute(FILE* file)
{
	yyin = file;
	yyparse();
	std::cout << "expressions num: " << MainExpressionsList::Instance().main_expressions_list_.size() << std::endl;
	fclose(file);
}
