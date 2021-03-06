#pragma once

#include <iostream>

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

	[[nodiscard]] virtual std::string ToString() const = 0;

	[[nodiscard]] virtual ExpressionType GetType() const = 0;

	[[nodiscard]] State GetState() const;
	
	[[nodiscard]] bool IsCalculated() const;

	virtual bool operator==(const Expression &expression) const = 0;

	virtual bool operator!=(const Expression &expression) const = 0;

	virtual void Calculate(ExpertSystemData &expert_system_data) = 0;

	virtual void UpdateState(State state);

protected:
	State state_ { False };
	bool is_calculated_ = false;
	
	class LogicContradictionException : public std::exception {
	public:
		LogicContradictionException(const std::string &exception);
		
		const char* what() const _NOEXCEPT override;
	
	private:
		std::string exception_;
	};
};

std::ostream &operator<<(std::ostream &os, const Expression &expression);
