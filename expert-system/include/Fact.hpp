#pragma once

#include "Node.hpp"

class Fact final : public INode {
public:
	explicit Fact(char name)
			: state_(Undetermined),
			  name_(name) {}

	State EvaluateState() override {
		return state_;
	}

	[[nodiscard]] char GetName() const {
		return name_;
	}

private:
	INode::State state_;
	char name_;
};