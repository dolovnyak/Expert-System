#pragma once

#include <vector>
#include <cstdio>

class Expression;

class ExpertSystem
{
public:
	void Setup(FILE *file);
	void Solve();

private:
	friend class Expression;

	std::vector<Expression *> main_expressions_;
	std::vector<Expression *> facts_;
	std::vector<Expression *> query_;

	std::vector<Expression *> FindAllOwners(Expression *expression);
};
