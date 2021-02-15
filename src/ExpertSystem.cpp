#include "ExpertSystem.hpp"
#include "MainExpressionsList.hpp"
#include "Visualizer.hpp"

extern void ShowExampleAppCustomNodeGraph(bool* opened);
int yyparse();
extern FILE *yyin;

ExpertSystem::ExpertSystem(bool visualModeOn) : visual_mode_on_(visualModeOn)
{}

void ExpertSystem::Execute(FILE* file)
{
	
	if (visual_mode_on_)
	{
		Visualizer visualizer;
		visualizer.SetupImgui();
		visualizer.Execute();
//		bool a = true;
//		ShowExampleAppCustomNodeGraph(&a);
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
