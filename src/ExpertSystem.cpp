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
	
	if (visual_mode_on_)
	{
		imgui_test();
//		each time when input in gui change need to get FILE* of this input and call 'yyin = file;' and 'yyparse'
	}
	else
	{
		yyin = file;
		yyparse();
		std::cout << "expressions num: " << MainExpressionsList::Instance().main_expressions_list_.size() << std::endl;
		fclose(file);
	}
}

void ExpertSystem::SetVisualMode(bool visual_mode_on)
{
	visual_mode_on_ = visual_mode_on;
}
