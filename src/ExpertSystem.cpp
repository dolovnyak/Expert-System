#include <chrono>
#include <iostream>

#include "ExpertSystem.hpp"
#include "ExpertSystemData.hpp"

int yyparse(ExpertSystemData *data);
extern FILE *yyin;

ExpertSystemData ExpertSystem::Parse(FILE *file) {
	yyin = file;

	ExpertSystemData data;
	yyparse(&data);
	fclose(file);

	return data;
}

void ExpertSystem::Solve(ExpertSystemData &expert_system_data) {
	for (const auto request : expert_system_data.GetQuery()) {
		request->Calculate(expert_system_data);
	}
}

void ExpertSystem::RaiseEvent(const IEvent &event) {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::ctime(&now) << ": " << event.ToString() << std::endl;
}
