#include "argparse/argparse.hpp"
#include "Grammar.yy.hpp"

extern int imgui_test();

//TODO when project will finish maybe delete generated grammar files from git
int yyparse();

int main(int argc, char **argv)
{
	imgui_test();
	yyparse();
}
