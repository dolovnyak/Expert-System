#pragma once

#include <iostream>

//#include "ExpertSystemData.hpp"

class ExpertSystemData;

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

	[[nodiscard]] State GetState() const;

	virtual bool operator==(const Expression &expression) const = 0;

	virtual bool operator!=(const Expression &expression) const = 0;


	virtual void Calculate(ExpertSystemData &expert_system_data);

	virtual void UpdateState(State state);

protected:
	State state_ { False };
};

std::ostream &operator<<(std::ostream &os, const Expression &expression);
