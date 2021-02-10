#pragma once

#include "Node.hpp"

class Fact final : public INode {
public:
	explicit Fact(char name)
			: name_(name) {}

	void UpdateState(std::shared_ptr<INode> sender) override {}

	void UpdateState(State state, std::shared_ptr<INode> sender) override {
		state_ = state;
		UpdateParents(SharedFromThis());
	}

	[[nodiscard]] char GetName() const {
		return name_;
	}

private:
	char name_;
};