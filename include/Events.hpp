#pragma once

#include "Expressions/Expression.hpp"

class IEvent {
public:
	explicit IEvent(Expression *expression) : expression_(expression) {}

	[[nodiscard]] virtual std::string ToString() const = 0;

protected:
	Expression *expression_;
};

class StateUpdatedEvent : public IEvent {
public:
	explicit StateUpdatedEvent(Expression *expression) : IEvent(expression) {}

	[[nodiscard]] std::string ToString() const override {
		return "State of " + expression_->ToString() + " updated to " + Expression::GetStateName(expression_->GetState());
	}
};