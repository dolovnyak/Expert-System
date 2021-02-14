#pragma once

#include <iostream>

class Expression
{
public:
	Expression() = default;
	virtual ~Expression() = default;
	
	virtual Expression* Find(Expression* expression) = 0;
	virtual std::string ToString() const = 0;
};

std::ostream &operator<<(std::ostream &os, const Expression& expression);


