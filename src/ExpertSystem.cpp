#include "ExpertSystem.hpp"
#include "MainExpressionsList.hpp"

extern int imgui_test();
int yyparse();
extern FILE *yyin;

ExpertSystem::ExpertSystem() : visual_mode_on_(false)
{
}

void ExpertSystem::Execute(FILE* file)
{
	yyin = file;
	yyparse();
	fclose(file);
	//after yyparse we have completely filled graph
	
	if (visual_mode_on_)
	{
		imgui_test();
	}
	else
	{
		std::cout << "expressions num: " << MainExpressionsList::Instance().main_expressions_list_.size() << std::endl;
	}
}

void ExpertSystem::SetVisualMode(bool visual_mode_on)
{
	visual_mode_on_ = visual_mode_on;
}
