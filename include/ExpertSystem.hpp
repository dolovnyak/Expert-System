#pragma once

#include <cstdio>

class ExpertSystem
{
public:
	ExpertSystem(bool visualModeOn);
	void Execute(FILE *file);

private:
	bool visual_mode_on_;
};
