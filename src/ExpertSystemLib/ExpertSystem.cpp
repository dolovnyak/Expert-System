#include "ExpertSystem.hpp"
#include "ExpertSystemData.hpp"

int yyparse(ExpertSystemData *data);
extern FILE *yyin;

ExpertSystemData *ExpertSystem::Parse(FILE *file) {
	yyin = file;

	auto data = new ExpertSystemData();
	yyparse(data);
	fclose(file);

	return data;
}

ExpertSystemData *ExpertSystem::Parse(char *str) {
	FILE *file = fmemopen(str, strlen(str), "r");
	
	yyin = file;
    auto data = new ExpertSystemData();
	yyparse(data);
	fclose(file);

	return data;
}

void ExpertSystem::Solve(ExpertSystemData &expert_system_data) {
	for (Expression *fact : expert_system_data.GetFacts()) {
		fact->Calculate(expert_system_data);
	}
	
	//check correct
	ExpertSystemData expert_system_data_for_check(expert_system_data);
	for (Expression *fact : expert_system_data_for_check.GetFacts()) {
		fact->Calculate(expert_system_data_for_check);
	}
}
