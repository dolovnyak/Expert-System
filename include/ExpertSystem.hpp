#pragma once

#include <vector>
#include <cstdio>

#include "ExpertSystemData.hpp"

class ExpertSystem {
public:
	static ExpertSystemData *Parse(FILE *file);
	static ExpertSystemData *Parse(char *str);
	static void Solve(ExpertSystemData &expert_system_data);
};
