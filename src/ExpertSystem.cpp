#include <chrono>
#include <iostream>

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
	
	ExpertSystemData expert_system_data_for_check1(expert_system_data);
	for (Expression *fact : expert_system_data_for_check1.GetFacts()) {
		fact->Calculate(expert_system_data_for_check1);
	}
	
	ExpertSystemData expert_system_data_for_check2(expert_system_data);
	expert_system_data_for_check2.ChangeAllMainExpressionOnMutualImplies();
	for (Expression *fact : expert_system_data_for_check2.GetFacts()) {
		fact->Calculate(expert_system_data_for_check2);
	}
}
