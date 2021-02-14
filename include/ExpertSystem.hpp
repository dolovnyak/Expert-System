#pragma once

#include <cstdio>

class ExpertSystem
{
public:
	ExpertSystem();
	void Execute(FILE *file);
	void SetVisualMode(bool visual_mode_on);

private:
	bool visual_mode_on_;
};
