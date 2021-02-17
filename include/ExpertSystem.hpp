#pragma once

#include <vector>
#include <cstdio>

#include "Events.hpp"
#include "ExpertSystemData.hpp"

class Expression;

class ExpertSystem
{
public:
	static ExpertSystemData Parse(FILE *file);
	static ExpertSystemData Parse(char *str);
	static void Solve(ExpertSystemData &expert_system_data);
	static void RaiseEvent(const IEvent &event);
};
