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
}

void ExpertSystem::RaiseEvent(const IEvent &event) {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::ctime(&now) << ": " << event.ToString() << std::endl;
}
