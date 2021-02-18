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
	static Expression::State GetMinState(Expression::State first, Expression::State second);
	static Expression::State GetMaxState(Expression::State first, Expression::State second);

public:
	Expression() = default;

	virtual ~Expression() = default;

	virtual Expression *Find(Expression *expression) = 0;

	virtual std::string ToString() const = 0;

	virtual ExpressionType GetType() const = 0;

	[[nodiscard]] State GetState() const;
	
	[[nodiscard]] bool IsCalculated() const;

	virtual bool operator==(const Expression &expression) const = 0;

	virtual bool operator!=(const Expression &expression) const = 0;

//	virtual void Calculate(ExpertSystemData &expert_system_data, std::vector<Expression *> ) = 0;
	virtual void Calculate(ExpertSystemData &expert_system_data) = 0;

	virtual void UpdateState(State state);

protected:
	State state_ { False };
	bool is_calculated_ = false;
};

std::ostream &operator<<(std::ostream &os, const Expression &expression);
