#pragma once

#include <iostream>

#include "ExpertSystem.hpp"

enum ExpressionType {
	FACT,
	UNARY,
	BINARY
};

class Expression {
public:
	enum State {
		False,
		Undetermined,
		True
	};

	static std::string GetStateName(State state);

public:
	Expression() = default;

	virtual ~Expression() = default;

	virtual Expression *Find(Expression *expression) = 0;

	virtual std::string ToString() const = 0;

	virtual ExpressionType GetType() const = 0;

	virtual bool operator==(const Expression &expression) const = 0;

	virtual bool operator!=(const Expression &expression) const = 0;

	virtual void Calculate(ExpertSystem &expert_system);

	[[nodiscard]] State GetState() const;

	virtual void UpdateState(State state);

protected:
	State state_;
};

std::ostream &operator<<(std::ostream &os, const Expression &expression);
